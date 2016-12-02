// Compilar usando:
//	g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
//	valgrind --leak-check=full ./tests

#include <string>
#include <iostream>
#include <fstream>

#include "Driver.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <math.h>

using namespace aed2;

////////////////////////////////////////////////////////////////
// ACERCA DE LA COMPLEJIDAD TEMPORAL
////////////////////////////////////////////////////////////////

void plotAgregarPokemon(int * xvals, double * yvals, double * yvals_ori, int nro_experimentos, double c1, double c2)
{
	//std::string plot_comand = "plot \"Agregar-Pokemon-Plot.dat\" using 1:2 t \"Mediciones del algoritmo\", \"Agregar-Pokemon-Plot.dat\" using 1:3 with lines t \""+ std::to_string(c1) +" * P + "+ std::to_string(c2) +" * EC log(EC)\" ";
	char plot_comand[200];
	sprintf(plot_comand, "plot \"Agregar-Pokemon-Plot.dat\" using 1:2 t \"Mediciones del algoritmo\", \"Agregar-Pokemon-Plot.dat\" using 1:3 with lines t \" %f * P + %f * EC log(EC)\" ", c1, c2);
	char * commandsForGnuplot[] = {	 "set title \"Complejidad temporal: agregarPokemon\"", 
											 "set xlabel \"Tamaño de la entrada: P + EC\"", 
											 "set ylabel \"Tiempo [us]\"", 
											 // "plot \"Agregar-Pokemon-Plot.dat\" using 1:2 t \"Mediciones del algoritmo\",
											 //  \"Agregar-Pokemon-Plot.dat\" using 1:3 with lines t \"Curva esperada\" ",
											 plot_comand,
											 "set term png",
											 "set output \"Agregar-Pokemon-Plot.png\"",
											 "replot",
											 "set term x11"};
 	FILE * temp = fopen("Agregar-Pokemon-Plot.dat", "w");	 
	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
	int i;
	for (i=0; i < nro_experimentos; i++)
	{
		fprintf(temp, "%d %lf %lf\n", xvals[i], yvals[i], yvals_ori[i]); //Write the data to a temporary file
	}
	for (i=0; i < 8; i++)
	{
		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
	}
}

void scatterAgregarPokemon(std::string title, std::string filename, int * ECs, int * Ps, double * yvals, int nro_experimentos)
{
	char * commandsForGnuplot[] = {  "set title \"Complejidad temporal: agregarPokemon\"", 
									 "set xlabel \"EC\"", 
									 "set ylabel \"P\"", 
									 "plot \"Agregar-Pokemon-Scatter.dat\" using 1:2:3 with points palette pointsize 3 pointtype 7 title \"Tiempo [us]\"",
									 "set term png",
									 "set output \"Agregar-Pokemon-Scatter.png\"",
									 "replot",
									 "set term x11"};
	FILE * temp = fopen("Agregar-Pokemon-Scatter.dat", "w");	 
	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
	int i,j;
	for (i=0; i < nro_experimentos; i++)
	{
		fprintf(temp, "%d %d %lf \n", ECs[i], Ps[i], yvals[i]); //Write the data to a temporary file
	}
	for (i=0; i < 8; i++)
	{
		fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
	}
}

bool calc_curva_esperada(double mediciones_esperadas[], double mediciones[], int n_max, int m_max, int nro_experimentos, double & c_1, double & c_2)
{
	long double umbral_ok = 1;
	double c1_max = 2;
	double c2_max = 2;
	int delta_n = n_max / ( nro_experimentos - 1 );
	int delta_m = m_max / ( nro_experimentos - 1 );
	long double min_max_error = 100000000.;
	long double max_error = -1;
	bool res = false;

	double c1_max_error = -1;
	double c2_max_error = -1;

	double c1_min_max_error = -1;
	double c2_min_max_error = -1;

	for(double c1 = 0.001; c1 < c1_max; c1+=0.001)
	{
		for(double c2 = 0.001; c2 < c2_max; c2+=0.001)
		{
			max_error = -1;
			for( int i = 0; i < nro_experimentos; i++ )
			{
				double n = delta_n * ( i + 1 );
				double m = delta_m * ( i + 1 );
				long double aux = fabs( c1 * n + c2 * m * log(m) - mediciones[i] );
				if( max_error < aux )
				{
					max_error = aux;
					c1_max_error = c1;
					c2_max_error = c2;
				}
			}

			if( min_max_error > max_error )
			{
				min_max_error = max_error;
				c1_min_max_error = c1_max_error;
				c2_min_max_error = c2_max_error;
			}
		}
	}


	for(int l = 0; l < nro_experimentos; l++)
	{
		double n = delta_n * ( l + 1 );
		double m = delta_m * ( l + 1 );
		mediciones_esperadas[l] = ( c1_min_max_error * n + c2_min_max_error * m * log(m) );
	}

	c_1 = c1_min_max_error;
	c_2 = c2_min_max_error;

}

void test_complejidad_agregarPokemon()
{
	// Se pretende complejidad: O( |P| + EC * log(EC) )
	// Donde |P| es el nombre más largo para un pokémon en el d.
	// EC es la máxima cantidad de jugadores esperando para atrapar un pokémon

	int P_max = 500;
	int EC_max = 700;

    int nro_experimentos = 100;
	int delta_P = P_max / ( nro_experimentos - 1 );
	int delta_EC = EC_max / ( nro_experimentos - 1 );

	double mediciones[nro_experimentos];
	double mediciones_esperadas[nro_experimentos];
	int ECs[nro_experimentos];
	int Ps[nro_experimentos];
	int entrada[nro_experimentos];

	double ti,tf;
	struct timeval tp;
	int rtn;

	for(int l = 0; l < nro_experimentos; l++)
	{
		Conj<Coordenada> cc;
		cc.Agregar(Coordenada(0,0));
		Driver d(cc);
		Pokemon nombre;

		int P = delta_P * (l + 1);
		for(int i = 0; i < P; i++)
		{
			nombre = nombre + 'a';
		}
		d.agregarPokemon(nombre, Coordenada(0,0));

		int EC = delta_EC * (l + 1);
		for(int i = 0; i < EC; i++)
		{
			int j = d.agregarJugador();
			d.conectarse(j, Coordenada(0,0));
		}

		double sum = 0.;
        for(int j = 0; j < 500; j++)
		{
			rtn = gettimeofday(&tp, NULL);
			ti = (long double)tp.tv_sec+(1.e-6)*tp.tv_usec;

			d.agregarPokemon(nombre, Coordenada(0,0));
			
			rtn = gettimeofday(&tp, NULL);
			tf = (long double)tp.tv_sec+(1.e-6)*tp.tv_usec;

			sum += (tf - ti);
		}

		ECs[l] = EC;
		Ps[l] = P;
		entrada[l] = P+EC;
		mediciones[l] = 1.e6 * ( sum / 500.);
	}

	double c1, c2;
	calc_curva_esperada(mediciones_esperadas,mediciones,P_max,EC_max,nro_experimentos, c1, c2);
	plotAgregarPokemon(entrada,mediciones,mediciones_esperadas,nro_experimentos, c1, c2);
	scatterAgregarPokemon("Complejidad temporal: agregarPokemon","Agregar-Pokemon-Scatter",ECs,Ps,mediciones,nro_experimentos);

}

int main(int argc, char **argv)
{
	
    test_complejidad_agregarPokemon();
	
    return 0;
}
