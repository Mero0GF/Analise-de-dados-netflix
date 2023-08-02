//------------------------------------------------------------
//Nome: Eric Akio Uchiyamada                TIA: 42107865
//Nome: Lucas Goulart de Farias Meres       TIA: 42127459
//Nome: Oliver Kieran Galvão McCormack      TIA: 42122058
//Nome: Pedro Loureiro Morone Branco Volpe  TIA: 42131936
//Nome: Renan Tagliaferro                   TIA: 42105846
//Nome: Thiago Leandro Liporace             TIA: 42128481
//------------------------------------------------------------
// NodeBST.h
#ifndef __NODE_BST_H__
#define __NODE_BST_H__

#include <string>
#include "ProgramaNetFlix.h"

class NodeBST
{
public:
	NodeBST(ProgramaNetFlix programa, NodeBST* parent = nullptr, NodeBST* left = nullptr, NodeBST* right = nullptr);
	~NodeBST();

	void CopyDataFrom(const NodeBST* node);

	ProgramaNetFlix GetPrograma() const;
	void SetPrograma(ProgramaNetFlix programa);

	NodeBST* GetParent() const;
	void SetParent(NodeBST* parent);

	NodeBST* GetLeft() const;
	void SetLeft(NodeBST* left);

	NodeBST* GetRight() const;
	void SetRight(NodeBST* right);

	bool IsRoot() const;
	bool IsLeaf() const;

	int GetDegree() const;
	int GetDepth() const;
	int GetHeight() const;

private:
	ProgramaNetFlix m_Programa;
	
	NodeBST* m_Parent;
	NodeBST* m_Left;
	NodeBST* m_Right;

	int GetDepthInternal(const NodeBST* node) const;
	int GetHeightInternal(const NodeBST* node) const;
};

#endif
