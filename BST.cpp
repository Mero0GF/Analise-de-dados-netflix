//------------------------------------------------------------
//Nome: Eric Akio Uchiyamada                TIA: 42107865
//Nome: Lucas Goulart de Farias Meres       TIA: 42127459
//Nome: Oliver Kieran Galvão McCormack      TIA: 42122058
//Nome: Pedro Loureiro Morone Branco Volpe  TIA: 42131936
//Nome: Renan Tagliaferro                   TIA: 42105846
//Nome: Thiago Leandro Liporace             TIA: 42128481
//------------------------------------------------------------
// BST.cpp
#include "NodeBST.h"
#include "BST.h"
#include "Utils.h"
#include <sstream>
#include <queue> // TraverseDepthOrderInternal


BST::BST()
	: m_Root(nullptr)
{
}

BST::~BST()
{
	Clear();
}

NodeBST* BST::GetRoot() const
{
	return m_Root;
}

bool BST::IsEmpty() const
{
	return m_Root == nullptr;
}

void BST::Clear()
{
	Destroy(m_Root);
	m_Root = nullptr;
}

void BST::Destroy(NodeBST* node)
{
	if (node != nullptr)
	{
		Destroy(node->GetLeft());
		Destroy(node->GetRight());

		delete node;
		node = nullptr;
	}
}

int BST::GetDegree() const
{
	return GetDegreeInternal(m_Root);
}

int BST::GetDegreeInternal(const NodeBST* node) const
{
	if (node != nullptr)
	{
		int left = GetDegreeInternal(node->GetLeft());
		int right = GetDegreeInternal(node->GetRight());
		return Utils::Max(node->GetDegree(), Utils::Max(left, right));
	}

	return 0;
}

int BST::GetHeight() const
{
	if (m_Root == nullptr)
		return -1;

	return m_Root->GetHeight();
}

std::string BST::TraverseInOrder() const
{
	return TraverseInOrderInternal(m_Root);
}

std::string BST::TraverseInOrderInternal(const NodeBST* node) const
{
	if (node != nullptr)
	{
		std::ostringstream oss;
		oss << TraverseInOrderInternal(node->GetLeft());
		oss << "ID: " << node->GetPrograma().GetId() << "\n";
		oss << TraverseInOrderInternal(node->GetRight());
		return oss.str();
	}
	return "";
}

std::string BST::TraversePreOrder() const
{
	return TraversePreOrderInternal(m_Root);
}

std::string BST::TraversePreOrderInternal(const NodeBST* node) const
{
	if (node != nullptr)
	{
		std::ostringstream oss;
		oss << "ID: " << node->GetPrograma().GetId() << "\n";
		oss << TraversePreOrderInternal(node->GetLeft());
		oss << TraversePreOrderInternal(node->GetRight());
		return oss.str();
	}

	return "";
}

std::string BST::TraversePostOrder() const
{
	return TraversePostOrderInternal(m_Root);
}

std::string BST::TraversePostOrderInternal(const NodeBST* node) const
{
	if (node != nullptr)
	{
		std::ostringstream oss;
		oss << TraversePostOrderInternal(node->GetLeft());
		oss << TraversePostOrderInternal(node->GetRight());
		oss << "ID: " << node->GetPrograma().GetId() << "\n";
		return oss.str();
	}

	return "";
}

std::string BST::TraverseDepthOrder() const
{
	return TraverseDepthOrderInternal(m_Root);
}

std::string BST::TraverseDepthOrderInternal(const NodeBST* node) const
{
	if (node != nullptr)
	{
		std::ostringstream oss;
		std::queue<const NodeBST*> queue;

		queue.push(node);

		while (!queue.empty())
		{
			const NodeBST* n = queue.front();
			queue.pop();

			oss << n->GetPrograma().GetId() << ' ';

			if (n->GetLeft() != nullptr)
				queue.push(n->GetLeft());

			if (n->GetRight() != nullptr)
				queue.push(n->GetRight());
		}

		return oss.str();
	}

	return "";
}

NodeBST* BST::FindMin() const
{
	return FindMinInternal(m_Root);
}

NodeBST* BST::FindMinInternal(NodeBST* node) const
{
	if (node == nullptr)
		return nullptr;
	else if (node->GetLeft() == nullptr)
		return node;
	else
		return FindMinInternal(node->GetLeft());
}

NodeBST* BST::FindMax() const
{
	return FindMaxInternal(m_Root);
}

NodeBST* BST::FindMaxInternal(NodeBST* node) const
{
	if (node == nullptr)
		return nullptr;
	else if (node->GetRight() == nullptr)
		return node;
	else
		return FindMaxInternal(node->GetRight());
}

NodeBST* BST::Predecessor(std::string id) const
{
	NodeBST* node = SearchInternal(m_Root, id);
	return node == nullptr ? nullptr : PredecessorInternal(node);
}

NodeBST* BST::PredecessorInternal(NodeBST* node) const
{
	if (node->GetLeft() != nullptr)
	{
		return FindMaxInternal(node->GetLeft());
	}
	else
	{
		NodeBST* current = node;
		NodeBST* currentParent = node->GetParent();
		while (currentParent != nullptr && current == currentParent->GetLeft())
		{
			current = currentParent;
			currentParent = current->GetParent();
		}

		return currentParent;
	}
}

NodeBST* BST::Successor(std::string id) const
{
	NodeBST* node = SearchInternal(m_Root, id);
	return node == nullptr ? nullptr : SuccessorInternal(node);
}

NodeBST* BST::SuccessorInternal(NodeBST* node) const
{
	if (node->GetRight() != nullptr)
	{
		return FindMinInternal(node->GetRight());
	}
	else
	{
		NodeBST* current = node;
		NodeBST* currentParent = node->GetParent();
		while (currentParent != nullptr && current == currentParent->GetRight())
		{
			current = currentParent;
			currentParent = current->GetParent();
		}

		return currentParent;
	}
}

NodeBST *BST::SearchWithNumberOfComparison(std::string id, int &count) const {
  return SearchInternalWithNumberOfComparison(m_Root, id, count);
}

NodeBST *BST::SearchInternalWithNumberOfComparison(NodeBST *node,
                                                   std::string id,
                                                   int &count) const {
  if (node == nullptr) {
    count++;
    return nullptr;
  } else if (node->GetPrograma().GetId() == id) {
    count++;
    return node;
  } else if (node->GetPrograma().GetId() > id) {
    count++;
    return SearchInternalWithNumberOfComparison(node->GetLeft(), id, count);
  } else {
    count++;
    return SearchInternalWithNumberOfComparison(node->GetRight(), id, count);
  }
}


NodeBST* BST::Search(std::string id) const
{
	return SearchInternal(m_Root, id);
}

NodeBST* BST::SearchInternal(NodeBST* node, std::string &id) const
{
	if (node == nullptr)
		return nullptr;
	else if (node->GetPrograma().GetId() == id)
		return node;
	else if (node->GetPrograma().GetId() > id)
		return SearchInternal(node->GetLeft(), id);
	else
		return SearchInternal(node->GetRight(), id);
}


NodeBST* BST::Insert(ProgramaNetFlix programa)
{
	if (IsEmpty())
	{
		m_Root = new NodeBST(programa);
		return m_Root;
	}
	std::string id = programa.GetId();
	return InsertInternal(m_Root, nullptr,id,programa);
}

NodeBST* BST::InsertInternal(NodeBST* node, NodeBST* parent,std::string &id, ProgramaNetFlix programa)
{
	if (node == nullptr)
		node = new NodeBST(programa, parent);
	else if (node->GetPrograma().GetId() == id)
		return nullptr; // Error! Cannot insert duplicate.
	else if (node->GetPrograma().GetId() > id)
		node->SetLeft(InsertInternal(node->GetLeft(), node, id, programa));
	else if (node->GetPrograma().GetId() < id)
		node->SetRight(InsertInternal(node->GetRight(), node, id, programa));

	return node;
}

void BST::Remove(std::string id)
{
	RemoveInternal(m_Root, id);
}

NodeBST* BST::RemoveInternal(NodeBST* node, std::string id)
{
	if (node == nullptr)
		return nullptr;
	else if (node->GetPrograma().GetId() == id)
		node = RemoveNode(node);
	else if (node->GetPrograma().GetId() > id)
		node->SetLeft(RemoveInternal(node->GetLeft(), id));
	else
		node->SetRight(RemoveInternal(node->GetRight(), id));
	
	return node;
}

NodeBST* BST::RemoveNode(NodeBST* node)
{
	NodeBST* parent = node->GetParent();

	// Case 1: The node to be removed is a leaf.
	if (node->IsLeaf())
	{
		UpdateParentChild(parent, node, nullptr);

		delete node;
		node = nullptr;
	}
	// Case 2: The node to be removed has no left child/subtree.
	else if (node->GetLeft() == nullptr)
	{
		NodeBST* newChild = node->GetRight();
		UpdateParentChild(parent, node, newChild);

		delete node;
		node = newChild;
	}
	// Case 3: The node to be removed has no right child/subtree.
	else if (node->GetRight() == nullptr)
	{
		NodeBST* newChild = node->GetLeft();
		UpdateParentChild(parent, node, newChild);

		delete node;
		node = newChild;
	}
	// Case 4: The node to be removed has both left and right children/subtrees.
	else
	{
		// To remove the node, we are reducing the problem to Case 3.
		// In this case, predecessor is located in the node's left child/subtree and
		// is the node that has no right child/subtree.
		NodeBST* predecessor = Predecessor(node->GetPrograma().GetId());

		// Instead of only updating pointers, we are copying the data from the
		// predecessor to the node pointer and then we remove the predecessor node.
		node->CopyDataFrom(predecessor);
		node->SetLeft(RemoveInternal(node->GetLeft(), predecessor->GetPrograma().GetId()));
	}

	return node;
}

void BST::UpdateParentChild(NodeBST* parent, const NodeBST* child, NodeBST* newChild)
{
	if (parent != nullptr)
	{
		if (parent->GetLeft() == child)
			parent->SetLeft(newChild);
		else
			parent->SetRight(newChild);
	}
	else
	{
		m_Root = newChild;
	}

	if (newChild != nullptr)
		newChild->SetParent(parent);
}
