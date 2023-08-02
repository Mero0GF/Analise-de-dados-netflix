//------------------------------------------------------------
//Nome: Eric Akio Uchiyamada                TIA: 42107865
//Nome: Lucas Goulart de Farias Meres       TIA: 42127459
//Nome: Oliver Kieran Galvão McCormack      TIA: 42122058
//Nome: Pedro Loureiro Morone Branco Volpe  TIA: 42131936
//Nome: Renan Tagliaferro                   TIA: 42105846
//Nome: Thiago Leandro Liporace             TIA: 42128481
//------------------------------------------------------------
#ifndef __PROG_NETFLIX__
#define __PROG_NETFLIX__

#include <iostream>
#include <string>
#include <vector>

class ProgramaNetFlix
{
public:
	ProgramaNetFlix(std::string id, 
		std::string title,
		std::string type,
		int release_year,
		std::string age_certification,
		std::string genres,
		float imdb_score,
		float tmdb_score,
		float tmdb_popularity
		);

	~ProgramaNetFlix();

	std::string GetId();
	void SetId(std::string id);

	std::string GetTitle();
	void SetTitle(std::string title);

	std::string GetType();
	void SetType(std::string type);

	int GetReleaseYear();
	void SetReleaseYear(int year);

	std::string GetAgeCertification();
	void SetAgeCertification(std::string ageCertification);

	std::string GetGenres();
	void SetGenres(std::string genres);

	float GetImdbScore();
	void SetImdbScore(float score);

	float GetTmdbScore();
	void SetTmdbScore(float t_score);

	float GetTmdbPopularity();
	void SetTmdbPopularity(float popularity);


private:
	std::string m_Id;
	std::string m_Title;
	std::string m_Type;
	int m_ReleaseYear;
	std::string m_AgeCertification;
	std::string m_Genres;
	float m_ImdbScore;
	float m_TmdbScore; 
	float m_TmdbPopularity; //Pontuação baseada em popularidade do tempo de vida da série/filme. Float e parece não ter máximo.
};


/*
 exemplo:
id, ts239188,
title,Kitz,
type, SHOW,
description,"A year after the tragic death of her brother, Lisi enters the decadent world of a Munich clique at a ski resort, but soon she kicks off an avalanche that reveals the truth behind the facade full of glamor, money and hedonism."
release_year,2021
age_certification,TV-MA,
runtime,44,
genres,"['drama', 'thriller']"
production_countries,"['AT', 'DE']"
seasons,1.0
imdb_id,tt12104930
imdb_score,5.7
imdb_votes, 2392.0
tmdb_popularity,5.661
tmdb_score,7.4


*/

#endif