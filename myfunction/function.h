#ifndef _FUNCTIONAL_H_
#define _FUNCTIONAL_H_
#include <iostream>
#include <memory>

template<class T>
class Function;

template<class Return, class...Args>
class Function<Return(Args...)>
{
  class MethodWrapper;
  std::shared_ptr<MethodWrapper> mMethodWarpper;
public:
  //Except Pointer to member.
  template<typename Method>
  Function(Method method)
    : mMethodWarpper(std::make_shared<MethodImpl<Method>>(std::move(method)))
    {

    }
  //For Pointer to Member
  template<typename This>
  Function(This* _this, Return (This::*memberFunction)(Args...))
    :mMethodWarpper(std::make_shared<MemberMethodImpl<This>>(_this, std::move(memberFunction)))
    {

    }

  Return operator()(Args... args)
  {
    return mMethodWarpper->invoke(std::forward<Args>(args)...);
  }
private:
  class MethodWrapper
  {
  public:
    virtual ~MethodWrapper() = default;
    virtual Return invoke(Args...) = 0;
  };
  template<class Method>
  class MethodImpl : public MethodWrapper
  {
  public:
    MethodImpl(Method method)
      : mMethod(std::move(method))
    {

    }
    Return invoke(Args... args) override
    {
      return mMethod(std::forward<Args>(args)...);
    }
    Method mMethod;
  };
  template<class This>
  class MemberMethodImpl : public MethodWrapper
  {
    This* mThis;
    typedef Return (This::*MemberFunction)(Args...);
    MemberFunction mMemberFunction;
  public:
    MemberMethodImpl(This* _this, MemberFunction memberfunction)
      : mThis(_this), mMemberFunction(memberfunction)
    {}
    Return invoke(Args... args) override
    {
      return (mThis->*mMemberFunction)(std::forward<Args>(args)...);
    }
  };
};


#endif

