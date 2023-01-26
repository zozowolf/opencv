/*************************************************
Affichage de la composante bleue d'une image
*************************************************/
#include <iostream> // bibliothèque de gestion des E/S
#include "FonctionsUtilesOpenCV.h"

using namespace std; // utilisation de l'espace de nommage standard

/*==============================================
Fonction principale
===============================================*/
int main()
{
	// Lecture d'une image et stockage dans la variable img
	Mat img = imread("./medias/placeStan.jpg");

	// Définition de variables utiles pour la récupération des pixels de l’image
	unsigned long** pixels = NULL;
	unsigned long** pixel2 = NULL;
	unsigned int largeur, hauteur, i, j;

	if (img.empty()) //test si l'image a pu être trouvée
	{
		cout << "Erreur : Image non chargée..!!" << endl;
		cin.get(); cin.ignore();
		return EXIT_FAILURE;
	}

	//=========== PASSAGE DE L'IMAGE EN BLEUE =========================
	// On convertit la frame en un tableau 2D nommé pixels et on alloue la mémoire
	frameToPixels(img, largeur, hauteur, pixels, true);
	frameToPixels(img, largeur, hauteur, pixel2, true);
	// On force à 0 les niveaux de rouge et de vert de chaque pixel de l'image
	

	for (i = 0; i < hauteur ; i++)
	{
		for (j = 0; j < largeur; j++)
			pixel2[i][j] = pixels[i][j];
	}

	for (i = 0; i < hauteur - 800; i++)
	{
		for (j = 0; j < largeur; j++)
			pixels[i + 800][j] = pixel2[i][j];
	}

	for (i = 0; i < hauteur/2; i++)
	{
		for (j = 0; j < largeur; j++)
			pixels[i][j] = pixels[(hauteur-1)-i][j];
	}


	// On stocke le tableau pixels dans la frame avant son affichage 

	PixelsToFrame(img, largeur, hauteur, pixels);
	//=========== FIN DES OPERATIONS DE MODIFICATION DES PIXELS ==========
	// Optionnel : on redimensionne la fenêtre avant affichage écran
	resize(img, img, Size(1024, hauteur * 1024 / largeur));

	imshow("Un informaticien de génie !", img); //affichage de l'image dans une fenêtre

	waitKey(0); // attente de l'appui sur une touche dans la fenêtre graphique

	// enregistrement de la nouvelle image
	imwrite("./medias/miroireplaceStan.jpg", img);
	cin.get(); cin.ignore();
	return EXIT_SUCCESS;
}