#include <iostream> // bibliothèque de gestion des E/S
#include "FonctionsUtilesOpenCV.h"

using namespace std; // utilisation de l'espace de nommage standard
int main()
{
	// Définition de variables utiles pour la récupération des pixels de l’image et du logo
	unsigned long** pixelsImage = NULL, ** pixelsLune = NULL;
	unsigned int largeurImage, hauteurImage, largeurLune, hauteurLune, i, j, ilune, jlune;

	// Lecture d'une image et stockage dans la variable img
	Mat imgPlaceStan = imread("./medias/placeStan.jpg");

	if (imgPlaceStan.empty()) //test si l'image a pu être trouvée
	{
		cout << "Erreur : Image de la place Stan non chargée..!!" << endl;
		cin.get(); cin.ignore();
		return EXIT_FAILURE;
	}

	Mat imgLune = imread("./medias/pleineLune.jpg");

	if (imgLune.empty()) //test si l'image a pu être trouvée
	{
		cout << "Erreur : Image de la lune non chargée..!!" << endl;
		cin.get(); cin.ignore();
		return EXIT_FAILURE;
	}

	// Conversion de l'image et du logo en tableaux 2D
	frameToPixels(imgPlaceStan, largeurImage, hauteurImage, pixelsImage, true);
	frameToPixels(imgLune, largeurLune, hauteurLune, pixelsLune, true);

	// On place la lune au bon endroit dans l'image
	// PARTIE A COMPLETER ICI …
	i = 2300;
	
	for (ilune = 0; ilune < hauteurLune; ilune++)
	{
		j = 2950;
		for (jlune = 0; jlune < largeurLune; jlune++)
		{
			pixelsImage[i][j] = pixelsLune[ilune][jlune];
			j++;
		}
		i++;
	}
	
	// On stocke le tableau pixels dans la frame avant son affichage 
	PixelsToFrame(imgPlaceStan, largeurImage, hauteurImage, pixelsImage);

	imwrite("./medias/PlaceStanAvecLune.jpg", imgPlaceStan); // enregistrement de la nouvelle image

	 // on redimensionne la fenêtre avant affichage écran
	resize(imgPlaceStan, imgPlaceStan, Size(1024, hauteurImage * 1024 / largeurImage));

	imshow("La plus belle place du monde !", imgPlaceStan); //affichage de l'image dans une fenêtre
	waitKey(0); // attente de l'appui sur une touche dans la fenêtre graphique

	cout << "Appuyer sur une touche dans la console pour terminer le programme " << endl;
	cin.get(); cin.ignore();
	return EXIT_SUCCESS;
}