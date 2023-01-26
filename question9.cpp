/*************************************************
Changement de luminosit� de l'image
*************************************************/
#include <iostream> // biblioth�que de gestion des E/S
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
	Mat imgEcran; // image pr�c�dente avec des dimensions compatibles �cran

	if (img.empty()) //test si l'image a pu �tre trouv�e
	{
		cout << "Erreur : Image non charg�e..!!" << endl;
		cin.get(); cin.ignore();
		return EXIT_FAILURE;
	}

	// R�cup�ration des pixels de l'image 
	unsigned long** pixels = NULL, ** memo = NULL;
	unsigned int largeur, hauteur, i, j;
	int luminosite = 0, oldLuminosite = -1;

	// On convertit la frame en un tableau 2D nomm� pixels et on alloue la m�moire
	frameToPixels(img, largeur, hauteur, pixels, true);

	// On m�morise les pixels de d�part dans un tableau nomm� memo
	frameToPixels(img, largeur, hauteur, memo, true);

	while (1)
	{
		//===================================================================
		// Modifier la variable luminosit� en l'incr�mentant ou la d�cr�mentant
		// en fonction de la touche appuy�e. 
		//...
		//
		//=====================================================================
		// Compl�tez le code qui suit aux endroits indiqu�s
		if (luminosite != oldLuminosite) // si la luminosit� a chang�
		{
			// Appeler la fonction changeLuminosite
			//�
			if (waitKey(50) == '+') //On attend pendant 50 millisecondes si on appuie sur '+'
			{
				//��� Ecrire le code pour �claircir ici
			}
			if (waitKey(50) == '-')
			{
				//��� Ecrire le code pour assombrir ici
			}

			// On stocke le tableau pixels dans la frame avant son affichage 
			PixelsToFrame(img, largeur, hauteur, pixels);

			// on redimensionne la fen�tre avant affichage �cran
			resize(img, imgEcran, Size(1024, hauteur * 1024 / largeur));

			imshow("Changement Luminosit�", imgEcran);

			// Recopier le tableau de pixels initial dans le tableau pixels
			//�
			oldLuminosite = luminosite;
		}
	}
	cin.get(); cin.ignore();
	return EXIT_SUCCESS;
}