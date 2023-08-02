//------------------------------------------------------------
//Nome: Eric Akio Uchiyamada                TIA: 42107865
//Nome: Lucas Goulart de Farias Meres       TIA: 42127459
//Nome: Oliver Kieran Galvão McCormack      TIA: 42122058
//Nome: Pedro Loureiro Morone Branco Volpe  TIA: 42131936
//Nome: Renan Tagliaferro                   TIA: 42105846
//Nome: Thiago Leandro Liporace             TIA: 42128481
//------------------------------------------------------------
#include "AVL.h"
#include "BST.h"
#include "ProgramaNetFlix.h"
#include "Utils.h"
#include <chrono>
#include <iostream>
#include <string>
// BST__________________________________________________________________________________________
void PrintNodeBST(NodeBST *node) {
  if (node == nullptr)
    return;
  std::cout << "\nID: " << node->GetPrograma().GetId() << "\n"
            << "Título: " << node->GetPrograma().GetTitle() << "\n"
            << "Tipo: " << node->GetPrograma().GetType() << "\n";
}

void InsertBST(BST *bst) {

  std::string id, title, type, age_certification, genres;
  int release_year;
  float imdb_score, tmdb_score, tmdb_popularity;
  std::cout << "Inserir na BST:";
  std::cout << "\nDigite o ID do programa: ";
  std::cin >> id;
  std::cout << "\nDigite o Titulo do programa: ";
  std::cin.ignore();
  std::getline(std::cin, title);
  std::cout << "\nDigite o Tipo do programa: ";
  std::cin >> type;
  std::cout << "\nDigite o ano de lançamento do programa: ";
  std::cin >> release_year;
  std::cout << "\nDigite a idade recomendada do programa: ";
  std::cin >> age_certification;
  std::cout << "\nDigite o Genero do programa: ";
  std::cin.ignore();
  std::getline(std::cin, genres);
  std::cout << "\nDigite o score do IMDB do programa: ";
  std::cin >> imdb_score;
  std::cout << "\nDigite o score do TMDB do programa: ";
  std::cin >> tmdb_score;
  std::cout << "\nDigite a Popularidade TMDB do programa: ";
  std::cin >> tmdb_popularity;

  ProgramaNetFlix programa =
      ProgramaNetFlix(id, title, type, release_year, age_certification, genres,
                      imdb_score, tmdb_score, tmdb_popularity);
  NodeBST *node = bst->Insert(programa);
  if (node) {
    std::cout << "Node inserted:\n";
    node = bst->Search(id);
    PrintNodeBST(node);
  } else
    std::cout << "*** ERROR! Couldn't insert node!\n";
}

void RemoveBST(BST *bst) {
  std::string id;
  std::cout << "Id para remover na BST: ";
  std::cin >> id;
  bst->Remove(id);
}

void SearchBST(BST *bst) {
  std::string num;int count = 0;
  std::cout << "Procure ID na BST: ";
  std::cin >> num;
  auto start = std::chrono::high_resolution_clock::now();
  NodeBST *node = bst->SearchWithNumberOfComparison(num,count);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> tempo1 = end - start;
  if (node) {
    std::cout << "\nNode found:" << "\nnº de comparações: " << count;
    PrintNodeBST(node);
  } else
    std::cout << "*** ERROR! Couldn't find node!\nnº de comparações: " << count << "\n";
  std::cout << "Tempo de execução para BST: " << tempo1.count()
            << " milisegundos\n";
}

void TraverseInOrderBST(BST *bst) {
  std::cout << bst->TraverseInOrder() << '\n';
}

void TraversePreOrderBST(BST *bst) {
  std::cout << bst->TraversePreOrder() << '\n';
}

void TraversePostOrderBST(BST *bst) {
  std::cout << bst->TraversePostOrder() << '\n';
}
// AVL____________________________________________________________________________________________
void PrintNodeAVL(NodeAVL *node) {
  if (node == nullptr)
    return;
  std::cout << "\nID: " << node->GetPrograma().GetId() << "\n"
            << "Título: " << node->GetPrograma().GetTitle() << "\n"
            << "Tipo: " << node->GetPrograma().GetType() << "\n";
}

void InsertAVL(AVL *avl) {
  std::string id, title, type, age_certification, genres;
  int release_year;
  float imdb_score, tmdb_score, tmdb_popularity;
  std::cout << "\nInserir na AVL:";
  std::cout << "\nDigite o ID do programa: ";
  std::cin >> id;
  std::cout << "\nDigite o Titulo do programa: ";
  std::cin.ignore();
  std::getline(std::cin, title);
  std::cout << "\nDigite o Tipo do programa: ";
  std::cin >> type;
  std::cout << "\nDigite o ano de lançamento do programa: ";
  std::cin >> release_year;
  std::cout << "\nDigite a idade recomendada do programa: ";
  std::cin >> age_certification;
  std::cout << "\nDigite os gêneros do programa: ";
  std::cin.ignore();
  std::getline(std::cin, genres);
  std::cout << "\nDigite o score do IMDB do programa: ";
  std::cin >> imdb_score;
  std::cout << "\nDigite o score do TMDB do programa: ";
  std::cin >> tmdb_score;
  std::cout << "\nDigite a Popularidade TMDB do programa: ";
  std::cin >> tmdb_popularity;

  ProgramaNetFlix programa =
      ProgramaNetFlix(id, title, type, release_year, age_certification, genres,
                      imdb_score, tmdb_score, tmdb_popularity);

  NodeAVL *node = avl->Insert(programa);
  if (node) {
    std::cout << "Node inserted:\n";
    node = avl->Search(id);
    PrintNodeAVL(node);
  } else
    std::cout << "*** ERROR! Couldn't insert node!\n";
}

void RemoveAVL(AVL *avl) {
  std::string id;
  std::cout << "Id para remover na AVL: ";
  std::cin >> id;
  avl->Remove(id);
}

void SearchAVL(AVL *avl) {
  std::string id;int count = 0;
  std::cout << "\nProcure o ID na AVL: ";
  std::cin >> id;
  auto start = std::chrono::high_resolution_clock::now();
  NodeAVL *node = avl->SearchWithNumberOfComparison(id,count);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> tempo2 = end - start;
  if (node) {
    std::cout << "\nNode found:" << "\nnº de comparações: " << count;
    PrintNodeAVL(node);
  }

  else
    std::cout << "*** ERROR! Couldn't find node!\nnº de comparações: " << count << "\n";
  std::cout << "Tempo de execução para AVL: " << tempo2.count()
            << " milisegundos\n";
}

void PredecessorAVL(AVL *avl) {
  std::string id;
  std::cout << "Find predecessor of: ";
  std::cin >> id;
  NodeAVL *node = avl->Predecessor(id);
  if (node)
    std::cout << "Predecessor of " << id << ":\n" << node->ToString();
  else
    std::cout << "*** ERROR! There is no predecessor of " << id << "!\n";
}

void SuccessorAVL(AVL *avl) {
  std::string id;
  std::cout << "Find successor of: ";
  std::cin >> id;
  NodeAVL *node = avl->Successor(id);
  if (node)
    std::cout << "Successor of " << id << ":\n" << node->ToString();
  else
    std::cout << "*** ERROR! There is no successor of " << id << "!\n";
}

void FindMinAVL(AVL *avl) {
  NodeAVL *node = avl->FindMin();
  if (node)
    std::cout << "Minimum:\n" << node->ToString();
  else
    std::cout
        << "*** ERROR! Couldn't find minimum (tree is probably empty...)\n";
}

void FindMaxAVL(AVL *avl) {
  NodeAVL *node = avl->FindMax();
  if (node)
    std::cout << "Maximum:\n" << node->ToString();
  else
    std::cout
        << "*** ERROR! Couldn't find maximum (tree is probably empty...)\n";
}

void TraverseInOrderAVL(AVL *avl) {
  std::cout << avl->TraverseInOrder() << '\n';
}

void TraversePreOrderAVL(AVL *avl) {
  std::cout << avl->TraversePreOrder() << '\n';
}

void TraversePostOrderAVL(AVL *avl) {
  std::cout << avl->TraversePostOrder() << '\n';
}

void ClearAVL(AVL *avl) { avl->Clear(); }

void WriteToFile(AVL *avl) {
  bool saved;
  saved = (SaveToArchive(avl, "arquivo_saída.csv"));
  if (saved)
    std::cout << "\nÁrvore salvada com sucesso!\n";
  else
    std::cout << "\nNão foi possível salvar a árvore no arquivo\n";
}

// MAIN____________________________________________________________________________________________
int main() {

  AVL *avl = new AVL();
  BST *bst = new BST();

  int option = 0;
  do {
    std::cout
        << "Netflix Dataset Analysis:"
        << "\n[1] Ler arquivo"
        << "\n[2] Verificar quais programas você pode assistir de acordo com sua idade:"
        << "\n[3] Mostrar 5 melhores filmes e 5 piores filmes"
        << "\n[4] Top 5 séries mais populares"
        << "\n[5] Comparar score da crítica(imdb) com o score do público(tmdb)"
        << "\n[6] Quantidade de filmes em cada categoria e suas respectivas porcentagens diante o total"
        << "\n[7] Porcentagem de filmes e de séries lançadas em determinado ano"
        << "\n[8] Inserir novo filme/série"
        << "\n[9] Procure por um filme/série"
        << "\n[10] Remover um filme/série"
        << "\n[11] Exibir a alturas das árvores"
        << "\n[12] Salvar no arquivo "
        << "\n[0] Encerrar\n"
        << "Option: ";

    std::cin >> option;
    std::cin.ignore();
    std::cout << '\n';

    std::string genre, id;

    int year;

    switch (option) {
    case 1:
      ReadArchiveToAVL(avl);
      ReadArchiveToBST(bst);
      break;
    case 2:
      CountPossibleShowsByRating(avl);
      break;
    case 3:
      std::cout << "Digite um gênero de filme em inglês: ";
      std::cin >> genre;
      std::cin.ignore();
      BestAndWorstScores(avl, genre);
      break;
    case 4:
      Top5PopSeries(avl);
      break;
    case 5:
      CompareScores(avl);
      break;
    case 6:
      GeneralGenrePercent(avl);
      break;
    case 7:
      std::cout << "\nDigite um ano: ";
      std::cin >> year;
      std::cin.ignore();
      MSRatio(avl, year);
      break;
    case 8:
      InsertBST(bst);
      InsertAVL(avl);
      break;
    case 9:
      SearchBST(bst);
      SearchAVL(avl);
      break;
    case 10:
      RemoveBST(bst);
      RemoveAVL(avl);
      break;
    case 11:
      std::cout << "\nAltura da árvore BST: " << bst->GetHeight() << "\n";
      std::cout << "Altura da árvore AVL: " << avl->GetHeight() << "\n";
      break;
    case 12:
      WriteToFile(avl);
      break;
    }

    std::cout << '\n';
  } while (option != 0);
  std::cout<< "\n\n\t\t\t\t\t***FIM***\n";
  delete avl;
  delete bst;
}
