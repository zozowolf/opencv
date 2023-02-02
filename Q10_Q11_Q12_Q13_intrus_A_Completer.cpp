/*************************************************
- Extraction de l'intrus dans l'image
- Binarisation
- Détection du centre de gravité de l'intrus
- Remplacement du fond
*************************************************/
#include <iostream> // bibliothèque de gestion des E/S
#include <conio.h>	// gestion de la console (ici _getch())
#include <windows.h>
#include "FonctionsUtilesOpenCV.h"

using namespace std; // utilisation de l'espace de nommage standard
const char ECHAP = 27;


/*==============================================
Fonction principale
===============================================*/
int main()
{
	// Prise en compte des accents
	// Il faudra choisir la police de caractères Consolas ou Lucida
	SetConsoleOutputCP(1252);

	// Définition de variables utiles pour la récupération des pixels de l’image et du Intrus
	unsigned long** pixelsImage = NULL, ** pixelsIntrus = NULL;
	unsigned int largeurImage, hauteurImage, largeurIntrus, hauteurIntrus, i, j;
	unsigned seuil = 10;
	int diffB, diffR, diffV;
	char touche;


	// Lecture d'une image et stockage dans la variable img
	Mat img = imread("./medias/fond.jpg");

	if (img.empty()) //test si l'image a pu être trouvée
	{
		cout << "Erreur : Image 1 non chargée..!!" << endl;
		system("pause"); // attente d'appui sur une touche
		return -1;
	}

	Mat intrus = imread("./medias/fondAvecIntrus.jpg");
	if (intrus.empty()) //test si l'image a pu être trouvée
	{
		cout << "Erreur : Image 2 non chargée ..!!" << endl;
		system("pause"); // attente d'appui sur une touche
		return -1;
	}

	// Conversion de l'image et du Intrus en tableaux 2D
	frameToPixels(img, largeurImage, hauteurImage, pixelsImage, true);
	frameToPixels(intrus, largeurIntrus, hauteurIntrus, pixelsIntrus, true);

	cout << "=============== DETECTION DE L'INTRUS ====================" << endl;
	cout << "Appuyez sur les touches + ou - dans la fenetre console pour augmenter ou diminuer le seuil de comparaison" << endl;
	cout << "Si c'est OK, appuyez sur ECHAP sur la fenetre image " << endl;
	cout << "==========================================================" << endl;
	while (1)
	{
		frameToPixels(intrus, largeurIntrus, hauteurIntrus, pixelsIntrus);

		//=========================================================
		//  Q10 
		// Extraire les pixels de l'intrus en tenant compte du seuil (que l'on peut faire varier 
		// quand on appuie sur les touches + et -
		// On compare chaque pixel de l’image avec le pixel associé de l’image avec intrus.
		// Si le rouge n’a pas trop changé, si le vert n’a pas trop changé et si le bleu
		// n’a pas trop changé alors on met du blanc.
		// ========================================================
		//...
		for (i = 0; i < hauteurImage; i++)
		{
			for (j = 0; j < largeurImage; j++)
			{
				diffB = niveauDeBleu(pixelsIntrus[i][j]) - niveauDeBleu(pixelsImage[i][j]);
				diffR = niveauDeRouge(pixelsIntrus[i][j]) - niveauDeRouge(pixelsImage[i][j]);
				diffV = niveauDeVert(pixelsIntrus[i][j]) - niveauDeVert(pixelsImage[i][j]);
				if (diffV <= seuil && diffR <= seuil && diffB <= seuil)
				{
					pixelsIntrus[i][j] =  0xFFFFFF;
				}
				
			}

		}

		// On stocke le tableau pixels dans la frame avant son affichage 
		PixelsToFrame(intrus, largeurImage, hauteurImage, pixelsIntrus);

		imshow("-Recherche de l'intrus ", intrus); //affichage de l'image dans une fenêtre

		// Attente pendant 30 millisecondes de l'appui sur ECHAP. Si oui, on sort de la boucle infinie
		if (waitKey(30) == ECHAP)
		{
			cout << "Touche ECHAP appuyée" << endl;
			system("pause");
			break;
		}
		if (_kbhit())	// si on appuie sur une touche
		{
			touche = _getch();  	// on stocke dans la variable touche le code la touche appuyée

			switch (touche)	// Etude de cas des touches appuyées
			{
			case '+':
				//...;
				seuil++;
				break;

			case'-':
				//...;
				seuil--;
				break;
			}
			cout << "Seuil=" << seuil << endl;
		}

	}

	imwrite("./medias/intrus.jpg", intrus);

	cout << "=============== Q11 : BINARISATION ====================" << endl;
	cout << "Appuyez sur + ou - dans la fenêtre console pour changer le seuil de binarisation" << endl;
	cout << "si c'est OK, appuyez sur ECHAP dur la fenetre image" << endl;
	cout << "=================================================" << endl;
	// On stocke le tableau pixels dans la frame avant son affichage 
	PixelsToFrame(intrus, largeurImage, hauteurImage, pixelsIntrus);

	while (1)
	{
		frameToPixels(intrus, largeurIntrus, hauteurIntrus, pixelsIntrus);

		// On binarise (passage en noir ou blanc)
		//...
		seuil = 128;
		for (i = 0; i < hauteurIntrus; i++)
		{
			for (j = 0; j < largeurIntrus; j++)
			{
				if (niveauDeGris(pixelsIntrus[i][j]) < seuil)
					pixelsIntrus[i][j] = 0x000000;
				if (niveauDeGris(pixelsIntrus[i][j]) > seuil)
					pixelsIntrus[i][j] = 0xFFFFFF;
			}
		}

		// On stocke le tableau pixels dans la frame avant son affichage 
		PixelsToFrame(img, largeurIntrus, hauteurIntrus, pixelsIntrus);

		imshow("Binarisation", img); //affichage de l'image dans une fenêtre

													  // Attente pendant 30 millisecondes de l'appui sur ECHAP. Si oui, on sort de la boucle infinie
		if (waitKey(30) == ECHAP)
		{
			cout << "Touche ECHAP appuyée" << endl;
			system("pause");
			break;
		}
		if (_kbhit())	// si on appuie sur une touche
		{
			touche = _getch();  	// on stocke dans la variable touche le code la touche appuyée

			switch (touche)	// Etude de cas des touches appuyées
			{
			case '+': 	seuil++;


				break;

			case'-':	seuil--;

				break;
			}
			cout << "Seuil=" << seuil << endl;
		}

	}

	imwrite("./medias/intrusNoirEtBlanc.jpg", img);

	cout << "=============== Q12 : EXTRACTION DU CENTRE DE GRAVITE====================" << endl;
	//...chercher le centre de gravité, puis dessiner autour un carré jaune et tracer une croix noire au centre
	int mi=0, mj=0, x,y,nb=0;
	for (i = 0; i < hauteurIntrus; i++)
	{
		for (j = 0; j < largeurIntrus; j++)
		{
			if (pixelsIntrus[i][j] == 0x000000)
			{
				mi += i;
				mj += j;
				nb++;
			}
		}
	}
	x = mj / nb;
	y = mi / nb;
	cout << x << " et " << y << endl;
	for (i = y-15; i < y+16; i++)
	{
		for (j = x-15; j < x+16; j++)
		{
			pixelsIntrus[i][j] = 0xFFFF00;
			if(i==y && j<x + 10 && j>x - 10)
				pixelsIntrus[i][j] = 0x000000;

			if(j == x && i<y + 10 && i>y - 10)
				pixelsIntrus[i][j] = 0x000000;
			
		}
	}

	// On stocke le tableau pixels dans la frame avant son affichage 
	PixelsToFrame(intrus, largeurImage, hauteurImage, pixelsIntrus);

	imshow("- Version de VR - de Centre de gravité", intrus); //affichage de l'image dans une fenêtre

	waitKey(0); // attente 

	//====================== Q13 : on change le fond de l'image ====================
	cout << "On change le fond de l'image " << endl;
	// Lecture d'une image et stockage dans la variable img
	img = imread("./medias/prison.jpg");

	if (img.empty()) //test si l'image a pu être trouvée
	{
		cout << "Erreur : Image 1 non chargée..!!" << endl;
		system("pause"); // attente d'appui sur une touche
		return -1;
	}
	// Conversion de l'image et du Intrus en tableaux 2D
	frameToPixels(img, largeurImage, hauteurImage, pixelsImage, true);

	//...

	for (i = 0; i < hauteurIntrus; i++)
	{
		for (j = 0; j < largeurIntrus; j++)
		{
			if (pixelsIntrus[i][j] == 0xFFFFFF)
				pixelsIntrus[i][j] = pixelsImage[i][j];
		}
	}

	// On stocke le tableau pixels dans la frame avant son affichage 
	PixelsToFrame(intrus, largeurImage, hauteurImage, pixelsIntrus);

	imshow("-Version de VR - Fond modifié", intrus); //affichage de l'image dans une fenêtre

	waitKey(0); // attente 


	system("pause");
	return 0; // sortie du programme
}
