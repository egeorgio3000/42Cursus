#ifndef LEGACYITERATOR_HPP
# define LEGACYITERATOR_HPP

# include <iostream>
# include <string>

template<typename T>
class LegacyIterator
{

	public:

		LegacyIterator();
		LegacyIterator( LegacyIterator const & src );
		~LegacyIterator();

		LegacyIterator &		operator=( LegacyIterator const & rhs );

	private:

};

std::ostream &			operator<<( std::ostream & o, LegacyIterator const & i );

#endif /* ************************************************** LEGACYITERATOR_H */