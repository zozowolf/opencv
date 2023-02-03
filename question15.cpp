/*************************************************
Affichage de la composante bleue d'une image
*************************************************/
#include <iostream> // biblioth�que de gestion des E/S
#include "FonctionsUtilesOpenCV.h" 
#include <math.h>

using namespace std; // utilisation de l'espace de nommage standard
/*==============================================
Fonction principale
===============================================*/
int main()
{
	// Lecture d'une image et stockage dans la variable img
	Mat img = imread("./medias/fond.jpg");
	
	// D�finition de variables utiles pour la r�cup�ration des pixels de l�image
	unsigned long** pixels = NULL, ** memo= NULL;
	unsigned int largeur, hauteur, largeurmemo, hauteurmemo, i, j;
	

	if (img.empty()) //test si l'image a pu �tre trouv�e
	{
		cout << "Erreur : Image non charg�e..!!" << endl;

		cin.get(); cin.ignore();
		return EXIT_FAILURE;
	}

	//=========== PASSAGE DE L'IMAGE EN BLEUE =========================
	// On convertit la frame en un tableau 2D nomm� pixels et on alloue la m�moire
	frameToPixels(img, largeur, hauteur, pixels, true);
	// On force � 0 les niveaux de rouge et de vert de chaque pixel de l'image
	frameToPixels(img, largeurmemo, hauteurmemo, memo, true);
	
	for (i = hauteur-251; i < hauteur; i++)
	{
		for (j = largeur-51; j < largeur; j++)
		{
			int bleu = 0, rouge = 0, vert = 0;
			for (int k = i - 2; k <= i + 2; k++)
			{
				
				for (int l = j - 2; l <= j + 2; l++)
				{
					if (k < hauteur && k > -1 && l > -1 && l < largeur)
					{
						bleu += niveauDeBleu(memo[k][l]);
						rouge += niveauDeRouge(memo[k][l]);
						vert += niveauDeVert(memo[k][l]);	
					}
				}
				
			}
			bleu = bleu / 25;
			rouge = rouge / 25;
			vert = vert / 25;
			pixels[i][j] = bleu + (vert << 8) + (rouge << 16);
		}
	}


	// On stocke le tableau pixels dans la frame avant son affichage 
	PixelsToFrame(img, largeur, hauteur, pixels);

	//=========== FIN DES OPERATIONS DE MODIFICATION DES PIXELS ==========
	// Optionnel : on redimensionne la fen�tre avant affichage �cran

	resize(img, img, Size(1024, hauteur * 1024 / largeur));

	imshow("Un informaticien de g�nie !", img); //affichage de l'image dans une fen�tre

	waitKey(0); // attente de l'appui sur une touche dans la fen�tre graphique

	// enregistrement de la nouvelle image
	imwrite("./medias/flou.jpg", img);

	cin.get(); cin.ignore();
	return EXIT_SUCCESS;
}
