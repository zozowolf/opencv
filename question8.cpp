// PROGRAMME D’INCRUSTATION A COMPLETER
#include <iostream> // bibliothèque de gestion des E/S
#include "FonctionsUtilesOpenCV.h"

using namespace std; // utilisation de l'espace de nommage standard
int main()
{
	// Définition de variables utiles pour la récupération des pixels de l’image et du message
	unsigned long** pixelsImage, ** pixelsMessage = NULL;
	unsigned int largeurImage, hauteurImage, largeurMessage, hauteurMessage, i, j, imessage, jmessage;

	// Lecture d'une image et stockage dans la variable img
	Mat img = imread("./medias/informaticien.jpg");

	if (img.empty()) //test si l'image a pu être trouvée
	{
		cout << "Erreur : Image non chargée..!!" << endl;
		cin.get(); cin.ignore();
		return EXIT_FAILURE;
	}

	Mat message = imread("./medias/evolution.jpg");

	if (message.empty()) //test si l'image a pu être trouvée
	{
		cout << "Erreur : Message non chargé..!!" << endl;
		cin.get(); cin.ignore();
		return EXIT_FAILURE;
	}

	// Conversion de l'image et du message en tableaux 2D
	frameToPixels(img, largeurImage, hauteurImage, pixelsImage, true);
	frameToPixels(message, largeurMessage, hauteurMessage, pixelsMessage, true);

	//.... PARTIE A COMPLETER ...

	for (i = 0; i < hauteurImage; i++)
	{
		for (j = 0; j < largeurImage; j++)
			pixelsImage[i][j] = ~pixelsImage[i][j] | ~pixelsMessage[i][j] ;
	}

	// On stocke le tableau pixels dans la frame avant son affichage 
	PixelsToFrame(img, largeurImage, hauteurImage, pixelsImage);

	imwrite("./medias/CombinaisonImages.jpg", img); // enregistrement de la nouvelle image
	// on redimensionne la fenêtre avant affichage écran

	resize(img, img, Size(1024, hauteurImage * 1024 / largeurImage));

	imshow("Combinaison d'images", img); //affichage de l'image dans une fenêtre

	waitKey(0); // attente de l'appui sur une touche dans la fenêtre graphique

	cout << "Appuyer sur une touche dans la console pour terminer le programme " << endl;
	cin.get(); cin.ignore();
	return EXIT_SUCCESS;
}
