//------------------------------------------------------------
//Nome: Eric Akio Uchiyamada                TIA: 42107865
//Nome: Lucas Goulart de Farias Meres       TIA: 42127459
//Nome: Oliver Kieran Galvão McCormack      TIA: 42122058
//Nome: Pedro Loureiro Morone Branco Volpe  TIA: 42131936
//Nome: Renan Tagliaferro                   TIA: 42105846
//Nome: Thiago Leandro Liporace             TIA: 42128481
//------------------------------------------------------------
// Utils.h
#ifndef __UTILS_H__
#define __UTILS_H__

#include "AVL.h"
#include "BST.h"
#include <vector>
namespace Utils
{
	template <typename T>
	static T Max(T l, T r)
	{
		return (l > r) ? l : r;
	}
}

void ReadArchiveToAVL(AVL* avl);
void ReadArchiveToBST(BST* bst);

bool SaveToArchive(AVL* avl,const std::string& filename);
void PutLine(NodeAVL* node, std::ofstream *ofs);

void BestAndWorstScores(AVL* avl, std::string genre);
void SearchMovies(NodeAVL* node, const std::string genre, std::string bestMovies[], float bestScores[], std::string worstMovies[], float worstScores[]);

void CountPossibleShowsByRating(AVL* avl);
void CountPossibleShowsByRatingInternal(NodeAVL* node, std::vector<std::string> ratingList, int printChoice, int& count, int& total);
std::vector<std::string> GetRatingList(int ageChoice);
bool isStringInVector(const std::vector<std::string>& ratingList, const std::string& rating);

void GeneralGenrePercentInternal(NodeAVL *root,std::string vetGenres[],int vetGenresCount[],int &total_genres,int &total_movies);
void GeneralGenrePercent(AVL *avl);


void Top5PopSeries(AVL* avl);
void Top5PopSeriesInternal(const NodeAVL* node, float top_pop[], std::string top_series[]);
void UpdateTop(float top_pop[], std::string top_series[], float score_pop, std::string series_title, int i);
void printAllTmdbScore(NodeAVL *node);


void CompareScores(AVL *avl);
void CompareOneScoresInternal(NodeAVL* node,const std::string id);
void CompareAllScoresInternal(NodeAVL* node, float &sumImdb, float &sumTmdb, int &count);

void MSRatio(AVL* avl, int year);
void CountMSInternal(const NodeAVL* node, int year, int titles[]);

#endif