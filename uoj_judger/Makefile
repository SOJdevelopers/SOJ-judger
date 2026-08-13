INCLUDE_PATH = include
CXXFLAGS = -I./include -O2 -std=c++14

EXE_CHECKER = \
	builtin/checker/acmp2 \
	builtin/checker/acmp3 \
	builtin/checker/acmp4 \
	builtin/checker/acmp5 \
	builtin/checker/acmp6 \
	builtin/checker/acmp7 \
	builtin/checker/acmp8 \
	builtin/checker/acmp9 \
	builtin/checker/acmp10 \
	builtin/checker/bcmp \
	builtin/checker/caseicmp \
	builtin/checker/casencmp \
	builtin/checker/casewcmp \
	builtin/checker/fcmp \
	builtin/checker/hcmp \
	builtin/checker/icmp \
	builtin/checker/lcmp \
	builtin/checker/ncmp \
	builtin/checker/rcmp2 \
	builtin/checker/rcmp3 \
	builtin/checker/rcmp4 \
	builtin/checker/rcmp5 \
	builtin/checker/rcmp6 \
	builtin/checker/rcmp7 \
	builtin/checker/rcmp8 \
	builtin/checker/rcmp9 \
	builtin/checker/rcmp10 \
	builtin/checker/uncmp \
	builtin/checker/wcmp \
	builtin/checker/yesno

EXE = main_judger \
	run/formatter \
	run/run_program \
	run/run_interaction \
	builtin/judger/judger \
	$(EXE_CHECKER)

all: $(EXE)

% : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -Wall -Wextra

run/run_program: include/uoj_env.h run/run_program_conf.h
run/run_interaction: include/uoj_env.h
	$(CXX) $(CXXFLAGS) $@.cpp -o $@ -pthread

run/formatter  : include/testlib.h

builtin/judger/judger: include
main_judger: include

$(EXE_CHECKER): include/testlib.h

clean:
	rm -f $(EXE)
