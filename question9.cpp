/*************************************************
Changement de luminosité de l'image
*************************************************/
#include <iostream> // bibliothèque de gestion des E/S
#include "FonctionsUtilesOpenCV.h"

using namespace std; // utilisation de l'espace de nommage standard
const char ECHAP = 27;

/*==============================================
Fonction principale
===============================================*/
int main()
{
	// Lecture d'une image et stockage dans la variable img
	Mat img = imread("./medias/informaticienGris.jpg");
	Mat imgEcran; // image précédente avec des dimensions compatibles écran

	if (img.empty()) //test si l'image a pu être trouvée
	{
		cout << "Erreur : Image non chargée..!!" << endl;
		cin.get(); cin.ignore();
		return EXIT_FAILURE;
	}

	// Récupération des pixels de l'image 
	unsigned long** pixels = NULL, ** memo = NULL;
	unsigned int largeur, hauteur, i, j;
	int luminosite = 0, oldLuminosite = -1;

	// On convertit la frame en un tableau 2D nommé pixels et on alloue la mémoire
	frameToPixels(img, largeur, hauteur, pixels, true);

	// On mémorise les pixels de départ dans un tableau nommé memo
	frameToPixels(img, largeur, hauteur, memo, true);

	while (1)
	{
		//===================================================================
		// Modifier la variable luminosité en l'incrémentant ou la décrémentant
		// en fonction de la touche appuyée. 
		//...
		//
		//=====================================================================
		// Complétez le code qui suit aux endroits indiqués
		if (luminosite != oldLuminosite) // si la luminosité a changé
		{
			// Appeler la fonction changeLuminosite
			//…
			if (waitKey(50) == '+') //On attend pendant 50 millisecondes si on appuie sur '+'
			{
				//……… Ecrire le code pour éclaircir ici
			}
			if (waitKey(50) == '-')
			{
				//……… Ecrire le code pour assombrir ici
			}

			// On stocke le tableau pixels dans la frame avant son affichage 
			PixelsToFrame(img, largeur, hauteur, pixels);

			// on redimensionne la fenêtre avant affichage écran
			resize(img, imgEcran, Size(1024, hauteur * 1024 / largeur));

			imshow("Changement Luminosité", imgEcran);

			// Recopier le tableau de pixels initial dans le tableau pixels
			//…
			oldLuminosite = luminosite;
		}
	}
	cin.get(); cin.ignore();
	return EXIT_SUCCESS;
}