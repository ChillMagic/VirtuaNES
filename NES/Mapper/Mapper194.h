//////////////////////////////////////////////////////////////////////////
// Mapper194 迷宮寺院ダババ                                             //
//////////////////////////////////////////////////////////////////////////
class	Mapper194 : public Mapper
{
public:
	Mapper194( NES* parent ) : Mapper(parent) {}

	void	Reset();
	void	Write(WORD addr, BYTE data);

protected:
private:
};
