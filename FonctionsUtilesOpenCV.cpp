/*************************************************
Fonctions utiles pour manipuler simplement 
les pixels d'une frame

Auteur : V ROBERT
Date : Janvier 2016
Version : 1.0
*************************************************/
#include <iostream> // bibliothèque de gestion des E/S
#include <conio.h>	// gestion de la console (ici _getch())
#include <windows.h>
#include "FonctionsUtilesOpenCV.h"

using namespace std; // utilisation de l'espace de nommage standard

/*==============================================
Fonction pour mémoriser la frame 
dans un tableau à deux dimensions

Entrée : frame dont les octets R,V,B sont stockés
à la suite dans le champ data
===============================================*/
void frameToPixels(Mat frame, unsigned & width, unsigned & height, unsigned long ** & pixels, bool allouerMemoire)
{
	unsigned i, j, x=0;
	width = frame.size().width;
	height = frame.size().height;

	if (allouerMemoire)
	{
		pixels = new unsigned long *[height];
		for (i = 0; i < height; i++)
			pixels[i] = new unsigned long[width];
	}

	for (i = height - 1; i >= 0; i--)
	{
		for (j = 0; j < width; j++)
		{
			pixels[i][j] = frame.data[x]  + (frame.data[x + 1] << 8) + (frame.data[x + 2]<<16);
			x += 3;
		}

		if (i == 0) break;
	}
}


/*==============================================
Fonction pour mémoriser les pixels lus
dans la frame

Entrée : Tableau à 2 dimensions
Sortie ; frame
===============================================*/
void PixelsToFrame(Mat & frame, unsigned width, unsigned height, unsigned long ** pixels)
{
	unsigned i, j, x = 0;

	for (i = height - 1; i >= 0; i--)
	{
		for (j = 0; j < width; j++)
		{
			frame.data[x+2] = (uchar)(pixels[i][j] >> 16);
			frame.data[x + 1] = (uchar)(pixels[i][j] >> 8);
			frame.data[x] = (uchar)pixels[i][j];
			x += 3;
		}

		if (i == 0) break;
	}
}


/*==============================================
Extraction du niveau de bleu
===============================================*/
unsigned char niveauDeBleu(unsigned long pixel)
{
	unsigned long result;
	// je ne garde que les bits de bleu
	result = pixel & 0xFF;
	return (unsigned char) result; // on retourne le niveau de bleu
}

/*==============================================
Extraction du niveau de vert
===============================================*/
unsigned char niveauDeVert(unsigned long pixel)
{
	unsigned long result;
	// je ne garde que les bits de vert
	result = pixel & 0xFF00;
	// Je décale le résultat de 8 bits à droite
	result >>= 8; // ou result = result >> 8 ;
	return (unsigned char) result; // on retourne le niveau de vert
}

/*==============================================
Extraction du niveau de rouge
===============================================*/
unsigned char niveauDeRouge(unsigned long pixel)
{
	unsigned long result;
	// je ne garde que les bits de vert
	result = pixel & 0xFF0000;
	// Je décale le résultat de 8 bits à droite
	result >>= 16; // ou result = result >> 8 ;
	return (unsigned char) result; // on retourne le niveau de vert
}

/*==============================================
Extraction du niveau de gris
===============================================*/
unsigned char niveauDeGris(unsigned char rouge, unsigned char vert, unsigned char bleu)
{
	unsigned char gris;
	gris = (rouge + vert + bleu) / 3;
	return gris;
}

/*==============================================
Extraction du niveau de gris d'un pixel
===============================================*/
unsigned char niveauDeGris(unsigned long pixel)
{
	unsigned char rouge, vert, bleu;
	rouge = niveauDeRouge(pixel);
	vert = niveauDeVert(pixel);
	bleu = niveauDeBleu(pixel);
	return niveauDeGris(rouge, vert, bleu);
}

/*==============================================
Passage en gris
===============================================*/
void passageEnGris(unsigned long & pixelATraiter)
{
	unsigned r, v, b, gris;
	// Appeler les fonctions de l’ex7 pour extraire r, v et b
	r = niveauDeRouge(pixelATraiter);
	v = niveauDeVert(pixelATraiter);
	b = niveauDeBleu(pixelATraiter);
	// Appeler la fonction de l’ex3 pour extraire le gris
	gris = niveauDeGris(r, v, b);
	// Reconstruire pixel pour y stocker le gris sur les
	// octets de Rouge, de Vert et de Bleu
	pixelATraiter = gris + (gris << 8) + (gris << 16);
}

