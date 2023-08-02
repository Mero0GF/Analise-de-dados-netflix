//------------------------------------------------------------
//Nome: Eric Akio Uchiyamada                TIA: 42107865
//Nome: Lucas Goulart de Farias Meres       TIA: 42127459
//Nome: Oliver Kieran Galvão McCormack      TIA: 42122058
//Nome: Pedro Loureiro Morone Branco Volpe  TIA: 42131936
//Nome: Renan Tagliaferro                   TIA: 42105846
//Nome: Thiago Leandro Liporace             TIA: 42128481
//------------------------------------------------------------
// BST.h
#ifndef __BST_H__
#define __BST_H__

#include "NodeBST.h"
#include "ProgramaNetFlix.h"

class BST {
public:
  BST();
  ~BST();

  NodeBST *GetRoot() const;

  bool IsEmpty() const;
  void Clear();

  int GetDegree() const;
  int GetHeight() const;

  std::string TraverseInOrder() const;
  std::string TraversePreOrder() const;
  std::string TraversePostOrder() const;
  std::string TraverseDepthOrder() const;

  NodeBST *FindMin() const;
  NodeBST *FindMax() const;

  NodeBST *Predecessor(std::string id) const;
  NodeBST *Successor(std::string id) const;

  NodeBST *SearchWithNumberOfComparison(std::string id, int &count) const;
  NodeBST *Search(std::string id) const;
  NodeBST *Insert(ProgramaNetFlix programa);
  void Remove(std::string id);

private:
  NodeBST *m_Root;

  void Destroy(NodeBST *node);

  int GetDegreeInternal(const NodeBST *node) const;

  std::string TraverseInOrderInternal(const NodeBST *node) const;
  std::string TraversePreOrderInternal(const NodeBST *node) const;
  std::string TraversePostOrderInternal(const NodeBST *node) const;
  std::string TraverseDepthOrderInternal(const NodeBST *node) const;

  NodeBST *FindMinInternal(NodeBST *node) const;
  NodeBST *FindMaxInternal(NodeBST *node) const;

  NodeBST *PredecessorInternal(NodeBST *node) const;
  NodeBST *SuccessorInternal(NodeBST *node) const;

  NodeBST *SearchInternalWithNumberOfComparison(NodeBST *node,std::string id,int &count) const;
  NodeBST *SearchInternal(NodeBST *node, std::string &id) const;
  NodeBST *InsertInternal(NodeBST *node, NodeBST *parent, std::string &id, ProgramaNetFlix programa);
  NodeBST *RemoveInternal(NodeBST *node, std::string id);
  NodeBST *RemoveNode(NodeBST *node);
  void UpdateParentChild(NodeBST *parent, const NodeBST *child,NodeBST *newChild);
};

#endif
