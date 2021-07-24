#include <iostream>
#include <vector>
using namespace std;
class Card
{
public:
	enum class Card_value
	{
		Ace = 1,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack = 10,
		Queen = 10,
		King = 10,
	};
	enum class Suit
	{
		Spades,
		Hearts,
		Diamonds,
		Clubs
	};
	Card(Card_value v, Suit s, bool p) : c_value(v), c_suit(s), card_position(p) {}
	void Flip()
	{
		card_position = !(card_position);
	}
	int GetValue() const
	{
		int value{};
		value = (int)c_value;
		return value;
	}
	friend ostream &operator<<(ostream &os, const Card &card)
	{
		const string Value[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
		const string Suit[] = { "s", "h", "d", "c" };
		if (card.card_position)
		{
			os << Value[(int)card.c_value] << Suit[(int)card.c_suit];
		}
		else
		{
			os << "XX";
		}
		return os;
	}

private:
	Card_value c_value;
	Suit c_suit;
	bool card_position{};
};

class Hand
{
public:
	virtual ~Hand()
	{
		Clear();
	}
	void Add(Card *pCard)
	{
		h_Cards.push_back(pCard);
	}
	void Clear()
	{
		vector<Card*>::iterator iter = h_Cards.begin();
		for (iter = h_Cards.begin(); iter != h_Cards.end(); ++iter)
		{
			delete *iter;
			*iter = 0;
		}
		h_Cards.clear();
	}
	int GetTotal() const
	{
		if (h_Cards.empty())
		{
			return 0;
		}
		if (h_Cards[0]->GetValue() == 0)
		{
			return 0;
		}
		int total = 0;
		vector<Card*>::const_iterator iter;
		for (iter = h_Cards.begin(); iter != h_Cards.end(); ++iter)
		{
			total += (*iter)->GetValue();
		}
		bool containsAce = false;
		for (iter = h_Cards.begin(); iter != h_Cards.end(); ++iter)
		{
			if ((*iter)->GetValue() == (int)Card::Card_value::Ace)
			{
				containsAce = true;
			}
		}
		if (containsAce && total <= 11)
		{
			total += 10;
		}
		return total;
	}

protected:
	vector<Card*> h_Cards;
};

class GenericPlayer : public Hand
{
public:
	GenericPlayer(const string &name) : g_Name(name) {}
	virtual ~GenericPlayer() {}
	virtual bool IsHitting() const = 0;
	bool IsBusted() const
	{
		return (GetTotal() > 21);
	}
	void Bust() const
	{
		cout << g_Name << "Перебор" << endl;
	}
	friend ostream &operator<<(ostream &os, const GenericPlayer &genericPlayer)
	{
		os << genericPlayer.g_Name << ": ";
		vector<Card*>::const_iterator pCard;
		if (!genericPlayer.h_Cards.empty())
		{
			for (pCard = genericPlayer.h_Cards.begin(); pCard != genericPlayer.h_Cards.end(); ++pCard)
			{
				os << *(*pCard) << "\t";
			}
			if (genericPlayer.GetTotal() != 0)
			{
				cout << "(" << genericPlayer.GetTotal() << ")";
			}
		}
		else
		{
			os << "пусто";
		}
		return os;
	}

protected:
	string g_Name;
};

class Player : public GenericPlayer
{
public:
	Player(const string &name) : GenericPlayer(name) {}
	virtual ~Player() {}
	virtual bool IsHitting() const
	{
		cout << g_Name << ", раздать ещё одну карту? (Y/N): ";
		char answer;
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Win() const
	{
		cout << g_Name << " выиграл." << endl;
	}
	void Lose() const
	{
		cout << g_Name << " проиграл." << endl;
	}
	void Push() const
	{
		cout << g_Name << " сыграл вничью." << endl;
	}
};

class House : public GenericPlayer
{
public:
	House(const string &name = "House") : GenericPlayer(name) {}
	virtual ~House() {}
	virtual bool IsHitting() const
	{
		if (GetTotal() <= 16)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void FlipFirstCard()
	{
		if (!(h_Cards.empty()))
		{
			h_Cards[0]->Flip();
		}
		else
		{
			cout << "Переворачивать нечего" << endl;
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	return 0;
}