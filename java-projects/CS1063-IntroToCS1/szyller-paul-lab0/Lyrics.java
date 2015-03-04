// Lyrics.java
// Paul Szyller
// Lab 0

public class Lyrics
  //This class prints out the lyrics to the song "L'hymne de nos campagnes" by the french group Tryo.
  //The song translates in english to "The anthem of our countryside."
{
  public static void main ( String [] args )
  {
    printHeader ();
    printVerse1 ();
    printChorus ();
    printVerse2 ();
    printChorus ();
    printVerse3 ();
  }
  
  public static void printHeader ()
    //This method prints out the header to the lab.
  {
    System.out.print ( "Lab 0 written by Paul Szyller\n" + 
                      "\"L'hymne de nos campagnes\" by Tryo\n" + 
                      "Lyrics from " + 
                      "http://lyricstranslate.com/en/l039hymne-de-nos-campagnes-anthem-our-countryside.html\n\n" );
  }
  
  public static void printVerse1 ()
    //This method prints out the first verse to the song.
  {
    System.out.println ( "Si tu es né dans une cité HLM\n" + 
                        "Je te dédicace ce poème\n" + 
                        "En espérant qu'au fond de tes yeux ternes\n" + 
                        "Tu puisses y voir un petit brin d'herbe\n" + 
                        "Et les mans faut faire la part des choses\n" + 
                        "Il est grand temps de faire une pause\n" + 
                        "De troquer cette vie morose\n" + 
                        "Contre le parfum d'une rose\n" );
  }
  
  public static void printVerse2 ()
    //This method prints out the second verse to the song.
  {
    System.out.println ( "Pas de boulot, pas de diplômes\n" + 
                        "Partout la même odeur de zone\n" + 
                        "Plus rien n'agite tes neurones\n" + 
                        "Pas même le shit que tu mets dans tes cônes\n" + 
                        "Va voir ailleurs, rien ne te retient\n" + 
                        "Va vite faire quelque chose de tes mains\n" + 
                        "Ne te retourne pas ici tu n'as rien\n" + 
                        "Et sois le premier à chanter ce refrain\n" );
  }
  
  public static void printVerse3 ()
    //This method prints out the third verse to the song.
  {
    System.out.println ( "Assieds-toi près d'une rivière\n" + 
                        "Ecoute le coulis de l'eau sur la terre\n" + 
                        "Dis-toi qu'au bout, hé ! il y a la mer\n" + 
                        "Et que ça, ça n'a rien d'éphémère\n" + 
                        "Tu comprendras alors que tu n'es rien\n" + 
                        "Comme celui avant toi, comme celui qui vient\n" + 
                        "Que le liquide qui coule dans tes mains\n" + 
                        "Te servira à vivre jusqu'à demain matin!" );
  }
  
  public static void printChorus ()
    //This method prints out the Chorus.
  {
    System.out.println ( "\tC'est l'hymne de nos campagnes\n" + 
                        "\tDe nos rivières, de nos montagnes\n" + 
                        "\tDe la vie man, du monde animal\n" + 
                        "\tCrie-le bien fort, use tes cordes vocales!\n" );
  }
}