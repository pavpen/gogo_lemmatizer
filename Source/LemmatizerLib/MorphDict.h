// ==========  This file is under  LGPL, the GNU Lesser General Public Licence
// ==========  Dialing Lemmatizer (www.aot.ru)
// ==========  Copyright by Alexey Sokirko

#ifndef AhoKorasickMorph_h
#define AhoKorasickMorph_h


#include "MorphAutomat.h"
#include "../MorphWizardLib/FormInfo.h"



struct CLemmaInfoAndLemma 
{
	int			m_LemmaStrNo;
	CLemmaInfo	m_LemmaInfo;

	bool operator < (const CLemmaInfoAndLemma& comparand) const 
	{
		if (m_LemmaInfo.m_FlexiaModelNo != comparand.m_LemmaInfo.m_FlexiaModelNo)
			return m_LemmaInfo.m_FlexiaModelNo < comparand.m_LemmaInfo.m_FlexiaModelNo;

		return m_LemmaStrNo < comparand.m_LemmaStrNo;
	};

};




class CMorphDict   
{
	
protected:
	
	CMorphAutomat*				m_pFormAutomat;

	vector<int>					m_ModelsIndex;
	
	

	struct IsLessMorphInterp 
	{
		const CShortStringHolder& m_SearchInfos;

		IsLessMorphInterp(const CShortStringHolder& SearchInfos) : m_SearchInfos(SearchInfos) {};

		bool	operator () (const CLemmaInfoAndLemma& comparand1, const char* comparand2) const
		{
			const char* base = m_SearchInfos[comparand1.m_LemmaStrNo].GetString();

			return strcmp(base, comparand2) < 0;
		};

	};
	IsLessMorphInterp m_SearchInfoLess;
	void	GetLemmaInfos (const string& Text, size_t TextPos, vector<CAutomAnnotationInner>& Infos) const;
	void	CreateModelsIndex();

public:
	vector<CFlexiaModel>		m_FlexiaModels;
	vector<CAccentModel>		m_AccentModels;
	CShortStringHolder			m_Bases;
	vector<CLemmaInfoAndLemma>	m_LemmaInfos;
	StringVector				m_Prefixes;
	vector<BYTE>				m_NPSs;

	CMorphDict(MorphLanguageEnum Language);
	virtual ~CMorphDict();
	void	InitAutomat(CMorphAutomat*	pFormAutomat);

	//  loading & saving
	bool	Load(string GrammarFileName);
	bool	Save(string GrammarFileName) const;
	
	
	void	PredictBySuffix (const string& Text, size_t& TextOffset, size_t MinimalPredictSuffixlen, vector<CAutomAnnotationInner>& Infos) const;
	string	GetAllMorphInterpsStr (const string& Text,const size_t TextPos, bool bFullInterp) const;
};



#endif
