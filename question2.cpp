/*************************************************
Affichage de la composante bleue d'une image
*************************************************/
#include <iostream> // biblioth?que de gestion des E/S
#include "FonctionsUtilesOpenCV.h"
using namespace std; // utilisation de l'espace de nommage standard
/*==============================================
Fonction principale
===============================================*/
int main()
{
	// Lecture d'une image et stockage dans la variable img
	Mat img = imread("./medias/gaston.jpg");

	// D?finition de variables utiles pour la r?cup?ration des pixels de l?image
	unsigned long** pixels = NULL;
	unsigned int largeur, hauteur, i, j;

	if (img.empty()) //test si l'image a pu ?tre trouv?e
	{
		cout << "Erreur : Image non charg?e..!!" << endl;

		cin.get(); cin.ignore();
		return EXIT_FAILURE;
	}

	//=========== PASSAGE DE L'IMAGE EN BLEUE =========================
	// On convertit la frame en un tableau 2D nomm? pixels et on alloue la m?moire
	frameToPixels(img, largeur, hauteur, pixels, true);
	// On force ? 0 les niveaux de rouge et de vert de chaque pixel de l'image

	for (i = 0; i < hauteur / 2; i++)
	{
		for (j = 0; j < largeur / 2; j++)
			pixels[i][j] = pixels[i][j] & 0xFF0000;
	}

	for (i = hauteur /2; i < hauteur; i++)
	{
		for (j = 0; j < largeur/2; j++)
			pixels[i][j] = pixels[i][j] & 0x00FF00;
	}

	for (i = 0; i < hauteur / 2; i++)
	{
		for (j = largeur/2; j < largeur ; j++)
			pixels[i][j] = pixels[i][j] & 0x0000FF;
	}

	for (i = hauteur / 2; i < hauteur; i++)
	{
		for (j = largeur /2 ; j < largeur ; j++)
			pixels[i][j] = pixels[i][j] & 0x00FFFF;
	}


	// On stocke le tableau pixels dans la frame avant son affichage 
	PixelsToFrame(img, largeur, hauteur, pixels);

	//=========== FIN DES OPERATIONS DE MODIFICATION DES PIXELS ==========
	// Optionnel : on redimensionne la fen?tre avant affichage ?cran

	resize(img, img, Size(1024, hauteur * 1024 / largeur));

	imshow("Un informaticien de g?nie !", img); //affichage de l'image dans une fen?tre

	waitKey(0); // attente de l'appui sur une touche dans la fen?tre graphique

	// enregistrement de la nouvelle image
	imwrite("./medias/4couleursGaston.jpg", img);

	cin.get(); cin.ignore();
	return EXIT_SUCCESS;
}
