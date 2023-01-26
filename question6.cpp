/*************************************************
Affichage de la composante bleue d'une image
*************************************************/
#include <iostream> // biblioth�que de gestion des E/S
#include "FonctionsUtilesOpenCV.h"

using namespace std; // utilisation de l'espace de nommage standard

/*==============================================
Fonction principale
===============================================*/
int main()
{
	// Lecture d'une image et stockage dans la variable img
	Mat img = imread("./medias/placeStan.jpg");

	// D�finition de variables utiles pour la r�cup�ration des pixels de l�image
	unsigned long** pixels = NULL;
	unsigned long** pixel2 = NULL;
	unsigned int largeur, hauteur, i, j;

	if (img.empty()) //test si l'image a pu �tre trouv�e
	{
		cout << "Erreur : Image non charg�e..!!" << endl;
		cin.get(); cin.ignore();
		return EXIT_FAILURE;
	}

	//=========== PASSAGE DE L'IMAGE EN BLEUE =========================
	// On convertit la frame en un tableau 2D nomm� pixels et on alloue la m�moire
	frameToPixels(img, largeur, hauteur, pixels, true);
	frameToPixels(img, largeur, hauteur, pixel2, true);
	// On force � 0 les niveaux de rouge et de vert de chaque pixel de l'image
	

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
	// Optionnel : on redimensionne la fen�tre avant affichage �cran
	resize(img, img, Size(1024, hauteur * 1024 / largeur));

	imshow("Un informaticien de g�nie !", img); //affichage de l'image dans une fen�tre

	waitKey(0); // attente de l'appui sur une touche dans la fen�tre graphique

	// enregistrement de la nouvelle image
	imwrite("./medias/miroireplaceStan.jpg", img);
	cin.get(); cin.ignore();
	return EXIT_SUCCESS;
}