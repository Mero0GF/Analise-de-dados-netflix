//------------------------------------------------------------
//Nome: Eric Akio Uchiyamada                TIA: 42107865
//Nome: Lucas Goulart de Farias Meres       TIA: 42127459
//Nome: Oliver Kieran Galvão McCormack      TIA: 42122058
//Nome: Pedro Loureiro Morone Branco Volpe  TIA: 42131936
//Nome: Renan Tagliaferro                   TIA: 42105846
//Nome: Thiago Leandro Liporace             TIA: 42128481
//------------------------------------------------------------
#include <iostream>
#include <string>
#include "ProgramaNetFlix.h"

ProgramaNetFlix::ProgramaNetFlix(std::string id, 
		                            std::string title,
		                            std::string type,
		                            int release_year,
		                            std::string age_certification,
		                            std::string genres,
		                            float imdb_score,
		                            float tmdb_score,
		                            float tmdb_popularity):
m_Id(id),
m_Title(title),
m_Type (type),
m_ReleaseYear(release_year),
m_AgeCertification(age_certification),
m_Genres(genres),
m_ImdbScore(imdb_score),
m_TmdbScore(tmdb_score),
m_TmdbPopularity(tmdb_popularity)
{
}

ProgramaNetFlix::~ProgramaNetFlix()
{
}

std::string ProgramaNetFlix::GetId()
{
	return m_Id;
}
void ProgramaNetFlix::SetId(std::string id)
{
	m_Id = id;
}

std::string ProgramaNetFlix::GetTitle()
{
	return m_Title;
}
void ProgramaNetFlix::SetTitle(std::string title)
{
	m_Title = title;
}

std::string ProgramaNetFlix::GetType() 
{
	return m_Type;
}
void ProgramaNetFlix::SetType(std::string type)
{
	m_Type = type;
}

int ProgramaNetFlix::GetReleaseYear()
{
	return m_ReleaseYear;
}
void ProgramaNetFlix::SetReleaseYear(int year)
{
	m_ReleaseYear = year;
}

std::string ProgramaNetFlix::GetAgeCertification()
{
	return m_AgeCertification;
}
void ProgramaNetFlix::SetAgeCertification(std::string ageCertification)
{
	m_AgeCertification = ageCertification;
}

std::string ProgramaNetFlix::GetGenres()
{
	return m_Genres;
}
void ProgramaNetFlix::SetGenres(std::string genres)
{
	m_Genres = genres;
}

float ProgramaNetFlix::GetImdbScore()
{
	return m_ImdbScore;
}
void ProgramaNetFlix::SetImdbScore(float score)
{
	m_ImdbScore = score;
}

float ProgramaNetFlix::GetTmdbScore()
{
	return m_TmdbScore;
}
void ProgramaNetFlix::SetTmdbScore(float t_score)
{
	m_TmdbScore = t_score;
}

float ProgramaNetFlix::GetTmdbPopularity()
{
	return m_TmdbPopularity;
}
void ProgramaNetFlix::SetTmdbPopularity(float popularity)
{
	m_TmdbPopularity = popularity;
}
