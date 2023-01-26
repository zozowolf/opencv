/*************************************************
Affichage de la composante bleue d'une image
*************************************************/
#include <iostream> // bibliothèque de gestion des E/S
#include "FonctionsUtilesOpenCV.h" 
#include <math.h>

using namespace std; // utilisation de l'espace de nommage standard
/*==============================================
Fonction principale
===============================================*/
int main()
{
	// Lecture d'une image et stockage dans la variable img
	Mat img = imread("./medias/gaston.jpg");

	// Définition de variables utiles pour la récupération des pixels de l’image
	unsigned long** pixels = NULL;
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
	// On force à 0 les niveaux de rouge et de vert de chaque pixel de l'image

	unsigned int R = 50, x0 = hauteur - 50, y0 = 50;

	for (i = hauteur - 100; i < hauteur; i++)
	{
		for (j = 0; j < R * 2; j = )
		{
			pixels[i][j] = pixels[i][j] & 0xFF0000;
		}

	}

	for (j = 0; j < largeur; j++)
	{
		for (i = 0; i < R * 2; i = )
		{
			pixels[i][j] = pixels[i][j] & 0xFF0000;
		}

	}




	// On stocke le tableau pixels dans la frame avant son affichage 
	PixelsToFrame(img, largeur, hauteur, pixels);

	//=========== FIN DES OPERATIONS DE MODIFICATION DES PIXELS ==========
	// Optionnel : on redimensionne la fenêtre avant affichage écran

	resize(img, img, Size(1024, hauteur * 1024 / largeur));

	imshow("Un informaticien de génie !", img); //affichage de l'image dans une fenêtre

	waitKey(0); // attente de l'appui sur une touche dans la fenêtre graphique

	// enregistrement de la nouvelle image
	imwrite("./medias/SchtroumpfGaston.jpg", img);

	cin.get(); cin.ignore();
	return EXIT_SUCCESS;
}
