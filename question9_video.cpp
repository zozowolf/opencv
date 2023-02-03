/*************************************************
Affichage de la Webcam
*************************************************/
#include <iostream> // bibliothèque de gestion des E/S
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include "FonctionsUtilesOpenCV.h"

using namespace std; // utilisation de l'espace de nommage standard
using namespace cv;
const char ECHAP = 27;
/*==============================================
Fonction principale
===============================================*/
int main()
{
	bool bSuccess;
	Mat frame;
	Mat imgEcran;
	VideoCapture cap("./medias/monaLisa.wmv"); // ouverture du flux caméra numéro 0

	if (!cap.isOpened()) // si échec, on quitte le programme
	{
		cout << "video non trouvée" << endl;
		cin.get(); cin.ignore();
		return EXIT_FAILURE;
	}
	// Récupération des pixels de l'image 
	unsigned long** pixels = NULL, ** memo = NULL;
	unsigned int largeur, hauteur, i, j;
	int luminosite = 0, oldLuminosite = -1;



	while (1)
	{
		bSuccess = cap.read(frame); // lecture d'une frame
		if (!bSuccess) //si échec, on sort de la boucle infinie
		{
			cout << "Impossible de lire le flux vidéo" << endl;
			break;
		}
		// On convertit la frame en un tableau 2D nommé pixels et on alloue la mémoire
		frameToPixels(frame, largeur, hauteur, pixels, true);

		// On mémorise les pixels de départ dans un tableau nommé memo
		frameToPixels(frame, largeur, hauteur, memo, true);

		//===================================================================
		// Modifier la variable luminosité en l'incrémentant ou la décrémentant
		// en fonction de la touche appuyée. 
		if (waitKey(50) == '+') //On attend pendant 50 millisecondes si on appuie sur '+'
		{


			luminosite += 5;
		}
		if (waitKey(50) == '-')
		{


			luminosite -= 5;
		}
		//=====================================================================
		// Complétez le code qui suit aux endroits indiqués
		if (luminosite != oldLuminosite) // si la luminosité a changé
		{
			cout << luminosite << endl;
			// Appeler la fonction changeLuminosite
			//…
			changeLuminosite(pixels, hauteur, largeur, luminosite);

			// On stocke le tableau pixels dans la frame avant son affichage 
			PixelsToFrame(frame, largeur, hauteur, pixels);

			// on redimensionne la fenêtre avant affichage écran
			resize(frame, imgEcran, Size(1024, hauteur * 1024 / largeur));

			

			// Recopier le tableau de pixels initial dans le tableau pixels
			//…
			for (i = 0; i < hauteur; i++)
			{
				for (j = 0; j < largeur; j++)
					pixels[i][j] = memo[i][j];
			}


			oldLuminosite = luminosite;
		}
		imshow("Changement Luminosité", imgEcran);

		imshow("Fenetre webcam", frame); //On attribue un titre à la fenêtre
		 // Attente pendant 30 millisecondes de l'appui sur ECHAP. Si oui, on sort
		if (waitKey(30) == ECHAP)
		{
			cout << "Touche ECHAP appuyée" << endl;
			break;
		}
	}
	cout << "Appuyer sur une touche dans la console pour terminer le programme " << endl;
	cin.get(); cin.ignore(); // attente d'appui sur une touche
	return EXIT_SUCCESS; // sortie du programme
}