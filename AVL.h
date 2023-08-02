//------------------------------------------------------------
//Nome: Eric Akio Uchiyamada                TIA: 42107865
//Nome: Lucas Goulart de Farias Meres       TIA: 42127459
//Nome: Oliver Kieran Galvão McCormack      TIA: 42122058
//Nome: Pedro Loureiro Morone Branco Volpe  TIA: 42131936
//Nome: Renan Tagliaferro                   TIA: 42105846
//Nome: Thiago Leandro Liporace             TIA: 42128481
//------------------------------------------------------------
// AVL.h
#ifndef __AVL_H__
#define __AVL_H__

#include "NodeAVL.h"

class AVL
{
public:
	AVL();
	~AVL();

	NodeAVL* GetRoot() const;

	bool IsEmpty() const;
	void Clear();

	int GetDegree() const;
	int GetHeight() const;

	std::string TraverseInOrder() const;
	std::string TraversePreOrder() const;
	std::string TraversePostOrder() const;

	NodeAVL* FindMin() const;
	NodeAVL* FindMax() const;

	NodeAVL* Predecessor(std::string id) const;
	NodeAVL* Successor(std::string id) const;

  NodeAVL* SearchWithNumberOfComparison(std::string id,int &count) const;
	NodeAVL* Search(std::string id) const;
	NodeAVL* Insert(ProgramaNetFlix programa);
	void Remove(std::string id);
  int GetCount();

private:
	NodeAVL* m_Root;
  int count;
	void Destroy(NodeAVL *node);
	
	int GetDegreeInternal(const NodeAVL* node) const;

	std::string TraverseInOrderInternal(const NodeAVL* node) const;
	std::string TraversePreOrderInternal(const NodeAVL* node) const;
	std::string TraversePostOrderInternal(const NodeAVL* node) const;

	NodeAVL* FindMinInternal(NodeAVL* node) const;
	NodeAVL* FindMaxInternal(NodeAVL* node) const;

	NodeAVL* PredecessorInternal(NodeAVL* node) const;
	NodeAVL* SuccessorInternal(NodeAVL* node) const;

  NodeAVL* SearchInternalWithNumberOfComparison(NodeAVL* node,std::string id,int &count) const;
	NodeAVL* SearchInternal(NodeAVL* node, std::string& id) const;
	NodeAVL* InsertInternal(NodeAVL* node, NodeAVL* parent,std::string id, ProgramaNetFlix programa);
	NodeAVL* RemoveInternal(NodeAVL* node, std::string id);
	NodeAVL* RemoveNode(NodeAVL* node);
	void UpdateParentChild(NodeAVL* parent, const NodeAVL* child, NodeAVL* newChild);

	NodeAVL* RotateLeft(NodeAVL* node);
	NodeAVL* RotateRight(NodeAVL* node);
	NodeAVL* RotateLeftRight(NodeAVL* node);
	NodeAVL* RotateRightLeft(NodeAVL* node);

	NodeAVL* Balance(NodeAVL* node);
};

#endif