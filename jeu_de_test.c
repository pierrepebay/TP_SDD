#include "jeu_de_test.h"

BEGIN_TEST_GROUP(NULL_FILE)


TEST(listJours) {
   semaine_t* tete_semaine = createAgendaFromFile("nulltest.txt");
   jourList_t*  list_jours = createJourList(tete_semaine, "Test", 2);

	CHECK (list_jours->deb == NULL);
}


/*
// pas de test mais un exemple simple de manipulation
TEST(AffichageA) {
   struct donnee essai;

   strcpy(essai.nom, "2048");
   strcpy(essai.alias, "loic");
   essai.score = 16000;

   printf("%s ", essai.nom);
   printf("%s ", essai.alias);
   printf("%d ", essai.score);

} */

/*
TEST(AffichageB) {
   struct donnee essai;
   strcpy(essai.nom, "pokemon GO");
   strcpy(essai.alias, "loic");
   essai.score = 498;

   afficherDonnee(stdout, essai); 

   // creation du flux de texte => buffer
   char buffer[1024];
   FILE * file = fmemopen(buffer, 1024, "w");
   REQUIRE ( NULL != file);

   afficherDonnee(file, essai);
   fclose(file);

   CHECK( 0 == strcmp(buffer, "pokemon GO : loic avec 498\n") );
}*/

/*
TEST(AffichageC) {
   donnee_t essai;
   strcpy(essai.nom, "overwatch");
   strcpy(essai.alias, "loic");
   essai.score = 2300;

   afficherDonnee(stdout, essai); 

   // creation du flux de texte => buffer
   char buffer[1024];
   FILE * file = fmemopen(buffer, 1024, "w");
   REQUIRE ( NULL != file);

   afficherDonnee(file, essai);
   fclose(file);

   CHECK( 0 == strcmp(buffer, "overwatch : loic avec 2300\n") );
} */

/*
TEST(Saisie) {
   struct donnee essai;
   char buffer[1024];
   strcpy(buffer, "rien\ndutout\n10");
   FILE * file = fmemopen(buffer, 1024, "r");
   // REQUIRE ( NULL != file);

   saisirDonnee(file, &essai);
   fclose(file);

   afficherDonnee(stdout, essai);

   CHECK(  0 == strcmp(essai.nom, "rien") );
   CHECK(  0 == strcmp(essai.alias, "dutout") );
   CHECK( 10 == essai.score );   
} */

/*
TEST(lectureFichier) {
   donnee_t tableau[TAILLE_MAX];
   int taille = 0;
   
   // test d'un fichier non existant
   taille = tableauFromFilename("inconnu.txt", tableau);      
   CHECK( 0 == taille );

   // test du fichier exemple
   taille = tableauFromFilename("jeu1.txt", tableau);

   REQUIRE( 2 == taille );
   CHECK  ( 0 == strcmp(tableau[0].nom, "2048"));
   CHECK  ( 0 == strcmp(tableau[0].alias, "loic")); // :-)
   CHECK  ( 64236 == tableau[0].score );
   CHECK  ( 0 == strcmp(tableau[1].nom, "Minecraft"));
   CHECK  ( 0 == strcmp(tableau[1].alias, "kiux")); 
   CHECK  ( 12304883 == tableau[1].score );
}
*/

END_TEST_GROUP(NULL_FILE)


int run_tests() {
	RUN_TEST_GROUP(NULL_FILE); 
 	return 0;
}
