//------------------------------------------------------------
//Nome: Eric Akio Uchiyamada                TIA: 42107865
//Nome: Lucas Goulart de Farias Meres       TIA: 42127459
//Nome: Oliver Kieran Galvão McCormack      TIA: 42122058
//Nome: Pedro Loureiro Morone Branco Volpe  TIA: 42131936
//Nome: Renan Tagliaferro                   TIA: 42105846
//Nome: Thiago Leandro Liporace             TIA: 42128481
//------------------------------------------------------------
// NodeAVL.cpp
#include "NodeAVL.h"
#include "Utils.h"
#include <sstream>
#include "ProgramaNetFlix.h"

NodeAVL::NodeAVL(ProgramaNetFlix programa, NodeAVL* parent, NodeAVL* left, NodeAVL* right)
	: m_Programa(programa)
	, m_Parent(parent)
	, m_Left(left)
	, m_Right(right)
	, m_BalanceFactor(0)
{
}

NodeAVL::~NodeAVL()
{
	m_Parent = nullptr;
	m_Left = nullptr;
	m_Right = nullptr;
}

void NodeAVL::CopyDataFrom(const NodeAVL* node)
{
	m_Programa = node->GetPrograma();
}

ProgramaNetFlix NodeAVL::GetPrograma() const
{
	return m_Programa;
}

void NodeAVL::SetPrograma(ProgramaNetFlix programa)
{
	m_Programa = programa;
}

NodeAVL* NodeAVL::GetParent() const
{
	return m_Parent;
}

void NodeAVL::SetParent(NodeAVL* parent)
{
	m_Parent = parent;
}

NodeAVL* NodeAVL::GetLeft() const
{
	return m_Left;
}

void NodeAVL::SetLeft(NodeAVL* left)
{
	m_Left = left;
}

NodeAVL* NodeAVL::GetRight() const
{
	return m_Right;
}

void NodeAVL::SetRight(NodeAVL* right)
{
	m_Right = right;
}

bool NodeAVL::IsRoot() const
{
	return m_Parent == nullptr;
}

bool NodeAVL::IsLeaf() const
{
	return m_Left == nullptr && m_Right == nullptr;
}

int NodeAVL::GetDegree() const
{
	int degree = 0;

	if (m_Left != nullptr)
		++degree;
	if (m_Right != nullptr)
		++degree;

	return degree;
}

int NodeAVL::GetDepth() const
{
	return GetDepthInternal(this);
}

int NodeAVL::GetDepthInternal(const NodeAVL* node) const
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

int NodeAVL::GetHeight() const
{
	return GetHeightInternal(this);
}

int NodeAVL::GetHeightInternal(const NodeAVL* node) const
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

int NodeAVL::GetBalanceFactor() const
{
	return m_BalanceFactor;
}

void NodeAVL::UpdateBalanceFactor()
{
	int leftHeight = m_Left == nullptr ? -1 : GetHeightInternal(m_Left);
	int rightHeight = m_Right == nullptr ? -1 : GetHeightInternal(m_Right);
	m_BalanceFactor = rightHeight - leftHeight;

	// Read the comments inside AVL::Balance().
	//m_BalanceFactor = leftHeight - rightHeight;
}

std::string NodeAVL::ToString() const
{
	std::ostringstream oss;

	oss 
		<< "ID: " << GetPrograma().GetId() << ")"
		<< " Parent:" << (m_Parent != nullptr ? m_Parent->GetPrograma().GetId() : "folha")
		<< " Left:" << (m_Left != nullptr ? m_Left->GetPrograma().GetId() : "folha")
		<< " Right:" << (m_Right != nullptr ? m_Right->GetPrograma().GetId() : "folha")
		<< " Degree: " << GetDegree()
		<< " Depth: " << GetDepth()
		<< " Height: " << GetHeight()
		<< " Balance: " << m_BalanceFactor << '\n';

	return oss.str();
}
