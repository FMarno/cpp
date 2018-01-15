#include <iostream>
#include <memory>

class E {

	public:
		virtual ~E() = default;
};

class Val : public E {
	public:
		int val_;
		Val(int val): val_(val) {}
		Val(Val&& v) = default;
};

class BinOp : public E {
	protected:
	public:
		std::unique_ptr<E> a_;
		std::unique_ptr<E> b_;
		BinOp(std::unique_ptr<E> a, std::unique_ptr<E> b):a_(std::move(a)),b_(std::move(b)){}
		BinOp(BinOp&& b) = default;
};

class Sum : public BinOp {
	public:
		Sum(std::unique_ptr<E> a, std::unique_ptr<E> b):BinOp(std::move(a),std::move(b)){}
		Sum(Sum&& sum) = default;
};

class REPL {
	public:
		void eval(E* expr){
			if (Val* v = dynamic_cast<Val*>(expr)){
				std::cout << v->val_;
			} if (Sum * s = dynamic_cast<Sum*>(expr)){
				eval(s->a_.get());
				std::cout << '+' << ' ';
				eval(s->b_.get());
			}
		}
};

int main(){
	std::unique_ptr<Val> a = std::make_unique<Val>(1);
	std::unique_ptr<Val> b = std::make_unique<Val>(2);
	std::unique_ptr<Sum> s = std::make_unique<Sum>(std::move(a),std::move(b));
	
	std::cout << "hello there" << '\n';
	REPL repl;
	repl.eval(s.get());
}
