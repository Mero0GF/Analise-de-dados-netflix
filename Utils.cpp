//------------------------------------------------------------
//Nome: Eric Akio Uchiyamada                TIA: 42107865
//Nome: Lucas Goulart de Farias Meres       TIA: 42127459
//Nome: Oliver Kieran Galvão McCormack      TIA: 42122058
//Nome: Pedro Loureiro Morone Branco Volpe  TIA: 42131936
//Nome: Renan Tagliaferro                   TIA: 42105846
//Nome: Thiago Leandro Liporace             TIA: 42128481
//------------------------------------------------------------
//Bibliotecas padrões para ler arquivos
#include <iostream>
#include <string>
#include <sstream>
#include <istream>
#include <fstream>
//Biblioteca para alterar strings
#include <algorithm>
//Biblioteca para definir pontos de precisão na impressão 
#include <iomanip>
//Importar arquivos 
#include "Utils.h"
#include "AVL.h"
#include "NodeAVL.h"
#include "ProgramaNetFlix.h"


float StringToFloatStandardizer(const std::string& input) {
  float output = 0.0;
  std::string cleanString;

  // Remove espaços em branco no início e no final da string
  cleanString = input;
  cleanString.erase(cleanString.begin(), std::find_if(cleanString.begin(), cleanString.end(), [](unsigned char ch) {
    return !std::isspace(ch);
  }));
  cleanString.erase(std::find_if(cleanString.rbegin(), cleanString.rend(), [](unsigned char ch) {
    return !std::isspace(ch);
  }).base(), cleanString.end());

  // Substitui vírgulas por pontos
  std::replace(cleanString.begin(), cleanString.end(), ',', '.');

  // Verifica se a string não está vazia após a limpeza
  if (!cleanString.empty()) {
    try {
      output = std::stof(cleanString);
    } catch (const std::invalid_argument& e) {
      std::cout << "Erro ao converter string para float: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Erro ao converter string para float: " << e.what() << std::endl;
    }
  }

  return output;
}

template <typename TreeType>// template para evitar codigo redundante para BST e AVL
void ReadArchiveToTree(TreeType* tree) {
  std::ifstream ifs;
  std::string str;
  int count = 1;
  try {
    ifs.open("titles_new.csv");
    if (ifs.is_open()) {
      std::getline(ifs, str);  // ler a primeira linha

      while (std::getline(ifs, str)) {
        ProgramaNetFlix data = ProgramaNetFlix("", "", "", 0, "", "", 0, 0, 0);
        // std::getline(ifs, str);
        std::istringstream iss(str);
        std::string id;
        std::string titulo;
        std::string tipo;
        std::string ano_string;
        std::string idadeIndicativa;
        std::string genero;
        std::string imdbScore_string;
        std::string tmdbScore_string;
        std::string tmdbPopularidade_string;
        std::getline(iss, id, ';');
        std::getline(iss, titulo, ';');
        std::getline(iss, tipo, ';');
        std::getline(iss, ano_string, ';');
        std::getline(iss, idadeIndicativa, ';');
        std::getline(iss, genero, ';');
        std::getline(iss, imdbScore_string, ';');
        std::getline(iss, tmdbPopularidade_string, ';');
        std::getline(iss, tmdbScore_string, ';');

        float imdbScore = 0.0, tmdbScore = 0.0, tmdbPopularidade = 0.0;
        int ano = 0;

        imdbScore = StringToFloatStandardizer(imdbScore_string);
        
        tmdbPopularidade = StringToFloatStandardizer(tmdbPopularidade_string);

        tmdbScore = StringToFloatStandardizer(tmdbScore_string);

        ano = std::stoi(ano_string);

        data.SetId(id);
        data.SetTitle(titulo);
        data.SetType(tipo);
        data.SetReleaseYear(ano);
        data.SetAgeCertification(idadeIndicativa);
        data.SetGenres(genero);
        data.SetImdbScore(imdbScore);
        data.SetTmdbScore(tmdbScore);
        data.SetTmdbPopularity(tmdbPopularidade);
        (*tree)->Insert(data);
        //std::cout << "linha " << count << " lida\n";
        count++;
      }
      
      ifs.close();
      std::cout << "Leitura do arquivo feita com sucesso!\n\n";
    }
  } catch (...) {
    std::cout << "\nNão foi possível ler o Arquivo\n";
  }
}

void ReadArchiveToAVL(AVL* avl)
{
  ReadArchiveToTree(&avl);
}
void ReadArchiveToBST(BST* bst)
{
  ReadArchiveToTree(&bst);
}

void PutLine(NodeAVL* node, std::ofstream *ofs){ //Inserir linha no arquivo de saída
  if(node != nullptr){
    
    PutLine(node->GetLeft(), ofs);
    PutLine(node->GetRight(), ofs);
    std::string line;
    std::string imdbScore = std::to_string(node->GetPrograma().GetImdbScore());//transformar o float em string
    std::string tmdbScore = std::to_string(node->GetPrograma().GetTmdbScore());//transformar o float em string
    std::string tmdbPopularity = std::to_string(node->GetPrograma().GetTmdbPopularity());//transformar o float em string
    std::string releaseYear = std::to_string(node->GetPrograma().GetReleaseYear());//transformar o int em string

    //gerar a linha
    line = node->GetPrograma().GetId() + ";" + node->GetPrograma().GetTitle() + ";" + node->GetPrograma().GetType() + ";" + releaseYear + ";" + node->GetPrograma().GetAgeCertification() + ";" + node->GetPrograma().GetGenres() + ";" + imdbScore + ";" + tmdbPopularity + ";" + tmdbPopularity;
    
    *ofs << line << std::endl; //insere a linha no arquivo
  }
  return;
}

bool SaveToArchive(AVL* avl,const std::string& filename){
  std::ofstream ofs;
  try{
    ofs.open(filename, std::ios::out);
    if(ofs.is_open()){
      std::string line = "id;title;type;release_year;age_certification;genres;imdb_score;tmdb_popularity;tmdb_score";
      NodeAVL *node = avl->GetRoot();
      ofs << line << std::endl;//insere a primeira liha
      PutLine(node, &ofs);//insere os nós
      ofs.close();
    }
    
  }
  catch(...){
    return false;
  }
  return true;
}

//-------------------------------------------------------------------------------------------------
//Relativos ao item 3 do Menu
const int TOP_5_MOVIES = 5;
const int BOTTOM_5_MOVIES = 5;

void SearchMovies(NodeAVL* node, const std::string genre, std::string bestMovies[TOP_5_MOVIES], float bestScores[TOP_5_MOVIES], std::string worstMovies[BOTTOM_5_MOVIES], float worstScores[BOTTOM_5_MOVIES]){
  if(node != nullptr){
    int flag = 0;
    if (node->GetPrograma().GetType() == "MOVIE") {
      // percorrer a string gênero do nó
      for (int i = 0; i < (node->GetPrograma().GetGenres()).length(); i++) {
        // verificar se achou uma letra igual a primeira letra do genero dado
        if (node->GetPrograma().GetGenres()[i] == genre[0]) {
          int count = 0;
          for (int j = 1; j < genre.length(); j++) {
            if (node->GetPrograma().GetGenres()[i + j] != genre[j])
              break;
            else {
              count++;
            }
          }
          if (count == genre.length() - 1) { //se achou o gênero correto
            flag = 1;
            break;
          }
        }
      }
      if(flag == 1){
        float movieScore = node->GetPrograma().GetImdbScore();
        std::string movieTitle = node->GetPrograma().GetTitle();
        
        if (movieScore > 0) {
          // Melhores notas
          for (int i = 0; i < TOP_5_MOVIES; i++) {
            if (movieScore > bestScores[i]) {
              for (int j = TOP_5_MOVIES - 1; j > i; j--) {
                bestScores[j] = bestScores[j - 1];
                bestMovies[j] = bestMovies[j - 1];
              }
              bestScores[i] = movieScore;
              bestMovies[i] = movieTitle;
              break;
            }
          }

          // Piores notas
          for (int i = 0; i < BOTTOM_5_MOVIES; i++) {
            if (worstScores[i] == 0.0 || movieScore < worstScores[i]) {
              for (int j = BOTTOM_5_MOVIES - 1; j > i; j--) {
                worstScores[j] = worstScores[j - 1];
                worstMovies[j] = worstMovies[j - 1];
              }
              worstScores[i] = movieScore;
              worstMovies[i] = movieTitle;
              break;
            }
          }
        }
      }      
    }
    SearchMovies(node->GetLeft(), genre, bestMovies, bestScores, worstMovies, worstScores);
    SearchMovies(node->GetRight(), genre, bestMovies, bestScores, worstMovies, worstScores);      
  }
}

void BestAndWorstScores(AVL* avl, std::string genre){
  NodeAVL* root = avl->GetRoot();
  std::string bestMovies[TOP_5_MOVIES];
  float bestScores[TOP_5_MOVIES];
  std::string worstMovies[BOTTOM_5_MOVIES];
  float worstScores[BOTTOM_5_MOVIES];

  for(int i = 0; i < TOP_5_MOVIES; i++){
    bestMovies[i] = "";
    bestScores[i] = 0.0;
  }

  for(int i = 0; i < BOTTOM_5_MOVIES; i++){
    worstMovies[i] = "";
    worstScores[i] = 0.0;
  }

  SearchMovies(root, genre, bestMovies, bestScores, worstMovies, worstScores);

  std::cout << "Melhores notas:\n";
  for(int i = 0; i < TOP_5_MOVIES; i++){
    std::cout << i+1 << ". " << bestMovies[i] << ": " << bestScores[i] << "\n";
  }

  std::cout << "\nPiores notas:\n";
  for(int i = 0; i < BOTTOM_5_MOVIES; i++){
    std::cout << i+1 << ". " << worstMovies[i] << ": " << worstScores[i] << "\n";
  }
}

//-------------------------------------------------------------------------------------------------
//Relativos ao item 2 do Menu
void CountPossibleShowsByRating(AVL* avl)
{
  int ageChoice, printChoice, count = 0, total = 1;
  std::vector<std::string> possibleRatings;
  std::cout << "Digite sua idade: ";// a partir da idade do usuario vai buscar os possíveis filmes e séries disponíveis para aquela faixa etária. alguém com mais de 17 anos pode assistir tudo.
  std::cin >> ageChoice;
  
  std::cout << "\nDeseja imprimir o nome dos filmes?(Aviso: pode ser uma lista enorme)" << "\n[1]SIM." << "\n[2]NAO.\n";//caso o usuario escolha sim, irá imprimir TODOS os filmes que pode assistir
  std::cin >> printChoice;

  possibleRatings = GetRatingList(ageChoice);// aqui é construida a lista de ratings que este usuário pode asistir a partir de sua idade, utilisando a estrutura de VLA "vector" do C++
  //com a lista em mãos vamos fazer a busca dos titulos que tem estes retings:
  CountPossibleShowsByRatingInternal(avl->GetRoot(), possibleRatings, printChoice, count, total);

  std::cout << "\n\nVocê pode assistir programas com as classificações \n";
  for (const auto& str : possibleRatings)
  {
      std::cout << str <<", ";
  }

  std::cout << "\nExistem " << count<< " progamas com esta(s) classificação(s).";
  float percentage;
  percentage = ((float) count / (float) total)*100;
  std::cout << "\nVocê Pode assistir " << percentage << "% dos Programas Totais, Programas totais = : "<<total ;
}

void CountPossibleShowsByRatingInternal(NodeAVL* node, std::vector<std::string> ratingList, int printChoice, int& count, int& total)
{
  if (node != nullptr)
  {
    total++;//count basico do total de programas
    if (isStringInVector(ratingList, node->GetPrograma().GetAgeCertification()))//metodo que confere se a string está presente na estrutura de vector criada, para saber se o programa pode ser assitido pelo usuário.
    {
      count++;//count basico dos filmes e series que podem ser asistidos
      if (printChoice == 1)// caso o usuário tenha escolhido imprirmir o nome de cada filme, ele é impresso aqui
        std::cout << "\nNome do programa : " << node->GetPrograma().GetTitle();
    }//abaixo o resto da arvore é percorrido recursivamente
    CountPossibleShowsByRatingInternal(node->GetLeft(), ratingList, printChoice, count, total);
    CountPossibleShowsByRatingInternal(node->GetRight(), ratingList, printChoice, count, total);
  }
  //foi escolhido não incluir programas sem classificação etária, que estão como uma string vazia na arvore, pois como não sabemos a classificação, pode potencialmente ser inadequado ao usuário atual.
}

std::vector<std::string> GetRatingList(int ageChoice)
{// resumo dos ratings, segundo a netflix:
  /*
  "TV-Y": It is specifically designed for young children, typically ages 2 to 6.
  "TV-G": suitable for all audiences
  "G": suitable for all ages. 
  "TV-Y7": children ages 7 and above.
  "PG": parental guidance for younger viewers. It is generally recommended for ages 7 and above.
  "TV-PG": parental guidance is advised. recommended for ages 7 and above.
  "PG-13": 13  parental guidance.
  "TV-14": Over 14 years of age. Parent guidance.
  "R": 17 parental supervision
  "TV-MA": program is intended for mature audiences  over 17.
  "NC-17": restricted to viewers who are 17 years old or older.
  */
  int i;
  std::string orderedRatings[11] = { "TV-Y","TV-G","G", "TV-Y7","TV-PG","PG","PG-13","TV-14","R","TV-MA","NC-17"};// lista em ordem crescente dos possíveis ratings
  std::vector<std::string> group;
  for (i = 0; i < 3;i++)
    group.push_back(orderedRatings[i]);//estes são os ratings liberados para todos, então são sempre incluidos
  if (ageChoice >= 7)
  {
    for (i = 3; i < 6;i++)
        group.push_back(orderedRatings[i]);//adiciona os para maiores de 7 anos
  }
  if (ageChoice >= 13)
    group.push_back(orderedRatings[6]);//maiores de 13
  if (ageChoice >= 14)
    group.push_back(orderedRatings[7]);//maiores de 14
  if (ageChoice >= 17)
  { 
    for (i = 8; i < 11;i++)
        group.push_back(orderedRatings[i]);//maiores de 17
  }
  return group;
}

bool isStringInVector(const std::vector<std::string>& ratingList, const std::string& rating) 
{// metodo simples que varre o vector e checa se cada filme tem um rating presente no vector.
  for (const auto& str : ratingList)//varre todos os elementos do vector, caham cada elemento de "str"
  {
    if (str == rating)//confere se o elemento é igual a posição atual no vector
      return true;
  }
  return false;// cai aqui se não achou o rating
}

//--------------------------------------------------------------------------------------------------
// Quantidade de filmes em cada categoria e suas devidas porcentagens diante o total .

void GeneralGenrePercent(AVL *avl){
  std::string vetGenres[30];
  float percentage = 0;
  int vetGenresCount[30],total_genres = 0,total_movies = 0;
  std::fill_n(vetGenres,30,"");
  std::fill_n(vetGenresCount,30,0);
  NodeAVL *root = avl->GetRoot();
  GeneralGenrePercentInternal(root,vetGenres,vetGenresCount,total_genres,total_movies);
  std::cout << "Numero total de categorias:" << total_genres << "\n";
  std::cout << "Numero de filmes em cada categoria e suas devidas porcentagens:\n";
  std::cout << "-------------------------------------------------------------------------\n";
  for (int i = 0;i < total_genres;i++){
    percentage = ((float)vetGenresCount[i]/(float)total_movies)*100;
    if (vetGenres[i] == ""){
      std::cout << "Filmes sem categoria" << ": " << vetGenresCount[i] << " -- " << percentage << "%\n";
    }
    else
    std::cout << vetGenres[i] << ": " << vetGenresCount[i] << " -- " << percentage << "%\n";
  }
  std::cout << "-------------------------------------------------------------------------\n";
}

void GeneralGenrePercentInternal(NodeAVL *node,std::string vetGenres[],int vetGenresCount[],int &total_genres,int &total_movies){
  if (node != nullptr){
    std::string genre = "";
    int count_check = 0;
    std::string all_genres = node->GetPrograma().GetGenres();
    for (int i = 0;i < all_genres.length();i++){ 
      if ((all_genres[i] == '[') || (all_genres[i] == ' ')){
        genre = "";
        i++;
        for (int j = 0;((all_genres[i] != ']') && (all_genres[i] != ','));j++){
          genre = genre + all_genres[i];
          i++;
        }
        if (total_genres == 0){ 
          vetGenres[0] = genre;
          vetGenresCount[0] = vetGenresCount[0] + 1;
          total_genres++;
          genre = "";
        }
        else{
          count_check = 0;
          for (int j = 0;j < total_genres;j++){
            if (vetGenres[j] != genre){
              count_check++;
            }
            else{
              vetGenresCount[j] = vetGenresCount[j] + 1;
            }
          }
          if (count_check == total_genres){
            vetGenres[total_genres] = genre;
            vetGenresCount[total_genres] = vetGenresCount[total_genres] + 1;
            genre = "";
            total_genres++;
          }
        }
      }
    }
    total_movies++;
    GeneralGenrePercentInternal(node->GetLeft(),vetGenres,vetGenresCount,total_genres,total_movies);
    GeneralGenrePercentInternal(node->GetRight(),vetGenres,vetGenresCount,total_genres,total_movies);
  }
}


//-------------------------------------------------------------------------------------------------
//Comparar score da imdb(critica) com o score tmdb(publico) de um filme/serie em especifico [pelo ID], ou todas as série e filmes.

void CompareScores(AVL *avl){
  int option = 0;
  NodeAVL *root = avl->GetRoot();
  //Menu interno de opções. Para um título especifico e para todos os títulos
	std::cout <<"Escolha a análise a ser realizada:\n"
     << "\n[1] Apenas para um título especifico"
     << "\n[2] Para Todos os Títulos de Filmes e Séries"
		 << "\nOption: ";
	 std::cin >> option;
   std::cin.ignore();
	 std::cout << '\n';
  // Se opção for apenas um título, pede o ID do título
  if (option == 1){
    std::string id;
    std::cout << "Digite o ID do filme/série: " << std::endl;
    std::getline(std::cin,id);
    //busca para um título 
    CompareOneScoresInternal(root, id);
    return;
  }
  // Se opção for para todos os títulos 
  if (option == 2){
    float sumImdb = 0.0;
    float sumTmdb = 0.0;
    int count = 0;
    // busca para todos os títulos
    CompareAllScoresInternal(root, sumImdb, sumTmdb, count);
    //realiza o cálculo da média da nota publica e da critica e a discrepancia destas.
    float mediaImdb = (sumImdb / count);
    float mediaTmdb = (sumTmdb / count);
    float discrepancia = mediaImdb - mediaTmdb; 
    
    std::cout << "\n--------------------------------------------------------------\n"
              << "\nComparação de todos as séries e filmes\n"
              << "Total de Séries e Filmes analisados: " << count                       << "\n"
                                                         << std::fixed << std::setprecision(2) 
              << "Média das notas da Crítica: "          << mediaImdb                   << "★\n"
              << "Média das notas do Público: "          << mediaTmdb                   << "★\n\n"
              << "Discrepância das médias das notas: "   << std::abs(discrepancia) * 10 << "% --> "
                                                         << std::abs(discrepancia)      << "★\n"
              ;
    // Realiza uma análise sobre a concordancia entre público e critica em relação a todos os títulos
    if(discrepancia <= 1 && discrepancia >= -1)
      std::cout << "Em média, Público e Critica concordam" << std::endl;
    else if(discrepancia >= 2.5 || discrepancia <= -2.5)
      std::cout << "Em média, Público e Critica discordam" << std::endl;
    else
      std::cout << "Em média, Público e Critica discordam razoavelmente" << std::endl;
    
    std::cout << "\n--------------------------------------------------------------\n\n";
    return;
  }
  else return;
}
// Análise para um título 
void CompareOneScoresInternal(NodeAVL* node,const std::string id){

  if (node != nullptr){
    // percorre a árvore até encontrar o ID do título desejado 
		if(node->GetPrograma().GetId() == id){
      //Ao encontrar armazena os valores do ImdbScore e TmdbScore. E obtém a discrepância entre eles
      float notaImdb = node->GetPrograma().GetImdbScore();
      float notaTmdb = node->GetPrograma().GetTmdbScore();
      float discrepancia = (node->GetPrograma().GetImdbScore()) - (node->GetPrograma().GetTmdbScore());
      //Caso os dados sejam nulos ignora o título 
      if (notaImdb == 0|| notaTmdb == 0){
    std::cout << "\n--------------------------------------------------------------\n"
              << "Dados insuficientes para gerar analise (nota Imdb ou nota Tmdb está(ão) vazio(s)"
              << "\n--------------------------------------------------------------\n\n";
        return;
      }
      // Mostra as informações em relação a esse título 
      std::cout 
        << "\n--------------------------------------------------------------\n"
        << "\nTítulo: "               << node->GetPrograma().GetTitle() << " | "
        << "Generos: "                << node->GetPrograma().GetGenres()<< "\n"
        << "Nota da crítica (IMDB): " << notaImdb                       << "★\n"
        << "Nota do público (TMDB): " << notaTmdb                       << "★\n\n"
                                      << std::fixed << std::setprecision(2) 
        << "Discrepância de notas: "  << std::abs(discrepancia) * 10    << "% --> "  
                                      << std::abs(discrepancia)         << "★\n"
        ;

      /*
      Realiza uma análise a partir dos dados desse título, dividindo em: 
      Filme de qualidade (se TmdbScore > 7) - 
      Filme Razoavel (se 5.5 >= TmdbScore < 7) - 
      Filme Ruim (se TmdbScore < 5.5) -
      /
      E dentro de cada uma dessas categorias, apresento o quanto a opinião crítica se assemelha a do público
      a partir da discrepância obtida acima
      */
      
      if (notaTmdb >= 7){
        if(discrepancia <= 1 && discrepancia >= -1)
          std::cout << "Filme/Série de qualidade | Critica concorda" << std::endl;
        else if(discrepancia >= 2.5 || discrepancia <= -2.5)
          std::cout << "Filme/Série de qualidade | Critica discorda" << std::endl;
        else
          std::cout << "Filme/Série de qualidade | Critica discorda razoavelmente" << std::endl;
      }
      else if (notaTmdb >= 5.5){
        if(discrepancia <= 1 && discrepancia >= -1)
          std::cout << "Filme/Série de qualidade mediana| Critica concorda" << std::endl;
        else if(discrepancia >= 2.5 || discrepancia <= -2.5)
          std::cout << "Filme/Série de qualidade mediana| Critica discorda" << std::endl;
        else
          std::cout << "Filme/Série de qualidade mediana| Critica discorda razoavelmente" << std::endl;
      }
      else{
        if(discrepancia <= 1 && discrepancia >= -1)
          std::cout << "Filme/Série ruim| Critica concorda" << std::endl;
        else if(discrepancia >= 2.5 || discrepancia <= -2.5)
          std::cout << "Filme/Série ruim| Critica discorda (mas ninguem liga)" << std::endl;
        else
          std::cout << "Filme/Série ruim| Critica discorda razoavelmente (mas ninguem liga)" << std::endl;
      }
      std::cout << "\n--------------------------------------------------------------\n";
      return;
    }
    // Traverse
		CompareOneScoresInternal(node->GetLeft(), id);
		CompareOneScoresInternal(node->GetRight(), id); 
	} 
}

void CompareAllScoresInternal(NodeAVL* node, float &sumImdb, float &sumTmdb, int &count){
  
  if (node != nullptr){
    // obtem dos dados relevantes para a análise
    float notaImdb = node->GetPrograma().GetImdbScore();
    float notaTmdb = node->GetPrograma().GetTmdbScore();
    
    //Caso os dados sejam nulos ignorar
    if (notaImdb != 0 && notaTmdb != 0){
      //realiza a somatória das notas, para posteriormente realizar a média
      sumImdb += notaImdb;
      sumTmdb += notaTmdb;
      count++;
    }
   // Traverse
	 CompareAllScoresInternal(node->GetLeft(), sumImdb, sumTmdb, count);
	 CompareAllScoresInternal(node->GetRight(), sumImdb, sumTmdb, count); 
	} 
}

//-------------------------------------------------------------------------------------------------

//Top 5 séries mais populares segundo a popularidade tmdb

const int TOP_POP_SERIES = 5;

void Top5PopSeries(AVL* avl)
{
  NodeAVL* m_Root = avl->GetRoot();
  
  //Lista dos valores númericos de popularidade das 5 séries mais populares
  float top_pop[TOP_POP_SERIES];

  //Lista dos nomes das 5 séries mais populares
  std::string top_series[TOP_POP_SERIES];

  for(int i = 0; i < TOP_POP_SERIES; i++)
  {
    top_pop[i] = 0.0;
    top_series[i] = "";
  }

  Top5PopSeriesInternal(m_Root, top_pop, top_series);

  //Imprime as top 5 séries mais populares e seus valores númericos de popularidade
  for(int i = 0; i < TOP_POP_SERIES; i++)
  {
    std::cout << i+1 << ". " << top_series[i] << ": " << std::fixed << std::setprecision(3) << top_pop[i] << std::endl;
  }
  
}

//Função que percorre a AVL em pré-ordem e insere nas listas o nome das top 5 séries mais populares (top_series[]) e seus valores numéricos de popularidade (top_pop[])
void Top5PopSeriesInternal(const NodeAVL* node, float top_pop[TOP_POP_SERIES], std::string top_series[TOP_POP_SERIES])
{
  float aux_pop = 0.0;
  std::string aux_series = "";
  
  if(node != nullptr)
  {
    if(node->GetPrograma().GetType() == "SHOW") //Verifica se o nó atual é uma série
    {
      
      for(int i = 0; i < TOP_POP_SERIES; i++) //Encontra as top 5 séries mais populares
      {
        
        if(top_pop[i] < node->GetPrograma().GetTmdbPopularity())
        {
          aux_pop = top_pop[i];
          aux_series = top_series[i];

          top_pop[i] = node->GetPrograma().GetTmdbPopularity();
          top_series[i] = node->GetPrograma().GetTitle();

          UpdateTop(top_pop, top_series, aux_pop, aux_series, i); //atualiza o ranking
          i = TOP_POP_SERIES; //saída do loop
        }
        
      }
      
    }

    Top5PopSeriesInternal(node->GetLeft(), top_pop, top_series);
    Top5PopSeriesInternal(node->GetRight(), top_pop, top_series);
  }
}

//Atualiza o ranking das top 5 séries com maior popularidade. Exemplo: Se foi encontrada uma série com mais popularidade que a de rank 2, a de rank 2 vira rank 3, a de rank 3 vira de rank 4 e assim por diante.
void UpdateTop(float top_pop[TOP_POP_SERIES], std::string top_series[TOP_POP_SERIES], float pop, std::string series_title, int i)
{
  float aux_pop = 0.0;
  std::string aux_series = "";

  if(i < TOP_POP_SERIES - 1)
  {
    aux_pop = top_pop[i+1];
    aux_series = top_series[i+1];

    top_pop[i+1] = pop;
    top_series[i+1] = series_title;

    UpdateTop(top_pop, top_series, aux_pop, aux_series, i+1);
  }
}

//-------------------------------------------------------------------------------------------------

//Porcentagem entre filmes e séries de um certo ano

void MSRatio(AVL* avl, int year)
{
  NodeAVL* m_Root = avl->GetRoot();
  
  int titles[3] = {0, 0, 0}; //Vetor para armazenar, respectivamente, o número de séries, filmes e títulos (séries+filmes) lançados no ano year

  CountMSInternal(m_Root, year, titles);

  float p_series = ((float) titles[0] / titles[2]) * 100; //Porcentagem de séries
  
  float p_movies = ((float) titles[1] / titles[2]) * 100; //Porcentagem de filmes

  std::cout << "\nDo total de " << titles[2] << " títulos lançados em " << year << ":\n\n" << 
    titles[0] << " foram séries (" << p_series << "% do total)\n\n" << 
    titles[1] << " foram filmes (" << p_movies << "% do total)" << std::endl;
  
}

//Percorre a AVL em pré-ordem e conta quantas séries, filmes e títulos no total foram lançados no ano year
void CountMSInternal(const NodeAVL* node, int year, int titles[3])
{
  if(node != nullptr)
  {
    if(node->GetPrograma().GetReleaseYear() == year)
    {
      if(node->GetPrograma().GetType() == "SHOW")
      {
        titles[0]++; //Incrementa o número de séries lançadas no ano year
        titles[2]++; //Incrementa o número de títulos lançados no ano year
      }

      else if(node->GetPrograma().GetType() == "MOVIE")
      {
        titles[1]++; //Incrementa o número de filmes lançados no ano year
        titles[2]++; //Incrementa o número de títulos lançados no ano year
      }
      
      
    }

    CountMSInternal(node->GetLeft(), year, titles);
    CountMSInternal(node->GetRight(), year, titles);
  }
}
