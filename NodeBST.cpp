//------------------------------------------------------------
//Nome: Eric Akio Uchiyamada                TIA: 42107865
//Nome: Lucas Goulart de Farias Meres       TIA: 42127459
//Nome: Oliver Kieran Galvão McCormack      TIA: 42122058
//Nome: Pedro Loureiro Morone Branco Volpe  TIA: 42131936
//Nome: Renan Tagliaferro                   TIA: 42105846
//Nome: Thiago Leandro Liporace             TIA: 42128481
//------------------------------------------------------------
// NodeBST.cpp
#include "NodeBST.h"
#include "Utils.h"

NodeBST::NodeBST(ProgramaNetFlix programa, NodeBST* parent, NodeBST* left, NodeBST* right)
	: m_Programa(programa)
	, m_Parent(parent)
	, m_Left(left)
	, m_Right(right)
{
}

NodeBST::~NodeBST()
{
	m_Parent = nullptr;
	m_Left = nullptr;
	m_Right = nullptr;
}

void NodeBST::CopyDataFrom(const NodeBST* node)
{
	m_Programa = node->GetPrograma();
}

ProgramaNetFlix NodeBST::GetPrograma() const
{
	return m_Programa;
}
void NodeBST::SetPrograma(ProgramaNetFlix programa)
{
	m_Programa = programa;
}

NodeBST* NodeBST::GetParent() const
{
	return m_Parent;
}

void NodeBST::SetParent(NodeBST* parent)
{
	m_Parent = parent;
}

NodeBST* NodeBST::GetLeft() const
{
	return m_Left;
}

void NodeBST::SetLeft(NodeBST* left)
{
	m_Left = left;
}

NodeBST* NodeBST::GetRight() const
{
	return m_Right;
}

void NodeBST::SetRight(NodeBST* right)
{
	m_Right = right;
}

bool NodeBST::IsRoot() const
{
	return m_Parent == nullptr;
}

bool NodeBST::IsLeaf() const
{
	return m_Left == nullptr && m_Right == nullptr;
}

int NodeBST::GetDegree() const
{
	int degree = 0;

	if (m_Left != nullptr)
		++degree;
	if (m_Right != nullptr)
		++degree;

	return degree;
}

int NodeBST::GetDepth() const
{
	return GetDepthInternal(this);
}

int NodeBST::GetDepthInternal(const NodeBST* node) const
{
	if (node->IsRoot())
	{
		return 0;
	}
	else
	{
		return 1 + GetDepthInternal(node->GetParent());
	}
}

int NodeBST::GetHeight() const
{
	return GetHeightInternal(this);
}

int NodeBST::GetHeightInternal(const NodeBST* node) const
{
	if (node == nullptr || node->IsLeaf())
	{
		return 0;
	}
	else
	{
		return 1 + Utils::Max(GetHeightInternal(node->GetLeft()), GetHeightInternal(node->GetRight()));
	}
}
