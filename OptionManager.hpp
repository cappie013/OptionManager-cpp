#ifndef				OPTIONMANAGER_H_
# define			OPTIONMANAGER_H_

# include			<map>
# include			<string>

// Generic class

class				Option
{
public:
  Option()
  {}
  virtual ~Option()
  {}

};

template			<typename T>
class				OptionValue : public Option
{
public:
  // ATTRIBUTS
private:
  T				value_;

  // CTOR - DTOR
public:
  OptionValue<T>(T value)
    : value_(value)
  {}
  virtual ~OptionValue<T>()
  {}
  OptionValue<T>(OptionValue const &);

  // OPERATOR
public:
  OptionValue &			operator=(OptionValue const &);

  // SETTER
public:
  void				set(T const &value) { this->value_ = value; }

  // GETTER
public:
  T const			&get(void) const { return this->value_; }
};


namespace			Manager
{
  class				OptionManager
  {
    // ATTRIBUTS
  private:
    typedef std::map<std::string, Option *>	optionMap;
    typedef optionMap::iterator			optionMapIT;
    typedef optionMap::const_iterator		optionMapConstIT;
    typedef std::pair<std::string, Option *>	optionPair;
    optionMap			collection_;

    // CTOR - DTOR
  public:
    ~OptionManager()
    {
      optionMapIT			optionActual = this->collection_.begin();
      optionMapIT			optionEnd = this->collection_.end();

      for (; optionActual != optionEnd; ++optionActual)
	{
	  delete optionActual->second;
	}
      this->collection_.clear();
    }

  private:
    OptionManager(void) {}

    OptionManager(OptionManager const &);

    // OPERATOR
  public:
    OptionManager &			operator=(OptionManager const &);

    // PRIVATE METHODS
  private:
    template <typename T>
    void				create_(std::string const &key, T const &value)
    {
      Option				*tmp = new OptionValue<T>(value);
      this->collection_.insert(optionPair(key, tmp));
    }

    // PUBLIC METHODS
  public:
    static OptionManager		&getInstance(void)
    {
      static OptionManager		that;

      return that;
    }

    template <typename T>
    void				add(std::string const &key, T const &value)
    {
      optionMapIT			option;

      if ((option = this->collection_.find(key)) != this->collection_.end())
	{
	  (dynamic_cast<OptionValue<T> *>(option->second))->set(value);
	}
      else
	{
	  this->create_(key, value);
	}
    }

    template <typename T>
    T					get(std::string const &key, T &value) const
    {
      optionMapConstIT			option;

      if ((option = this->collection_.find(key)) != this->collection_.end())
	{
	  value = (dynamic_cast<OptionValue<T> *>(option->second))->get();
	}
      return value;
    }

    template <typename T>
    OptionValue<T>			*get(std::string const &key) const
    {
      optionMapConstIT			option;

      if ((option = this->collection_.find(key)) != this->collection_.end())
	{
	  return (dynamic_cast<OptionValue<T> *>(option->second));
	}
      return NULL;
    }
  };
}

#endif				/* !OPTIONMANAGER_H_ */
