#include "uoj_judger.h"

struct SubtaskInfo {
	bool passed;
	string info;
	int score;

	SubtaskInfo() {}
	SubtaskInfo(const bool &_p, const string &_i, const int &_s)
		: passed(_p), info(_i), score(_s) {}
};

void ordinary_test() {
	int n = conf_int("n_tests", 10);
	int m = conf_int("n_ex_tests", 0);
	int nT = conf_int("n_subtasks", 0);

	if (!conf_is("submit_answer", "on")) {
		report_judge_status_f("Compiling");
		RunCompilerResult c_ret = !conf_is("with_implementer", "on") ? compile("answer") : compile_with_implementer("answer");
		if (!c_ret.succeeded)
			end_judge_compile_error(c_ret);
	}

	bool passed = true;
	if (nT == 0) {
		for (int i = 1; i <= n; i++) {
			report_judge_status_f("Judging Test #%d", i);
			PointInfo po = test_point("answer", i);
			passed &= po.scr == 100;
			po.scr = scale_score(po.scr, conf_int("point_score", i, 100 / n));
			add_point_info(po);
		}
	} else if (nT == 1) {
		string type = conf_str("subtask_type", 1, "packed");

		if (type == "packed") ;
		else if (type == "min") tot_score = 100;
		else end_judge_judgement_failed("Unrecognized subtask type : \"" + type + "\".");
		
		for (int i = 1; i <= n; i++) {
			report_judge_status_f("Judging Test #%d", i);
			PointInfo po = test_point("answer", i);
			if (type == "packed") {
				if (po.scr == 100) {
					po.scr = i == 1 ? 100 : 0;
					add_point_info(po);
				} else {
					passed = false;
					po.scr = i == 1 ? 0 : -100;
					add_point_info(po);
					break;
				}
			} else if (type == "min") {
				po.scr < tot_score ? tot_score = po.scr : 0;
				add_point_info(po, false);
				if (po.scr != 100) passed = false;
				if (po.scr == 0) break;
			}
		}
	} else {
		map <int, SubtaskInfo> subtasks;
		for (int t = 1; t <= nT; t++) {
			string subtaskType = conf_str("subtask_type", t, "packed");
			int startI = conf_int("subtask_end", t - 1, 0) + 1;
			int endI = conf_int("subtask_end", t, 0);
			int dependNum;
			vector<PointInfo> points;
			vector<int> dependences;

			if (subtaskType == "packed") ;
			else if (subtaskType == "min") ;
			else if (subtaskType == "sum") ;
			else end_judge_judgement_failed("Unrecognized subtask type : \"" + subtaskType + "\".");

			if (conf_str("subtask_dependence", t, "none") == "many") {
				string cur = "subtask_dependence_" + vtos(t);
				for (int p = 1; dependNum = conf_int(cur, p, 0); ++p)
					dependences.push_back(dependNum);
			} else if (dependNum = conf_int("subtask_dependence", t, 0))
				dependences.push_back(dependNum);

			if (!dependences.empty() && subtaskType == "sum")
				end_judge_judgement_failed("Type \"sum\" subtask can't have dependencies.");

			int tfull = conf_int("subtask_score", t, 100 / nT);
			int tscore = tfull, cscore = 100;
			bool first = true;
			string info = "Accepted";

			int num_dependences = dependences.size();
			for (int i = 0; i < num_dependences && cscore > 0; ++i) {
				int num = dependences[i];
				PointInfo po(-1, subtasks[num].score, NAN, num, subtasks[num].info, "", "", "");
				if (subtaskType == "packed") {
					if (po.scr == 100) {
						po.scr = first ? tfull : 0, first = false;
						cscore = 100;
						points.push_back(po);
					} else {
						passed = false;
						po.scr = first ? 0 : -tfull, first = false;
						cscore = 0;
						points.push_back(po);
						info = po.info;
					}
				} else if (subtaskType == "min") {
					po.scr < cscore ? cscore = po.scr : 0;
					points.push_back(po);
					if (po.scr != 100) passed = false, info = po.info;
					if (po.scr == 0) {info = po.info; break;}
				} else abort();
			}

			for (int i = startI; i <= endI && cscore > 0; i++) {
				report_judge_status_f("Judging Test #%d of Subtask #%d", i, t);
				PointInfo po = test_point("answer", i);
				if (subtaskType == "packed") {
					if (po.scr == 100) {
						po.scr = first ? tfull : 0, first = false;
						cscore = 100;
						points.push_back(po);
					} else {
						passed = false;
						po.scr = first ? 0 : -tfull, first = false;
						cscore = 0;
						points.push_back(po);
						info = po.info;
						break;
					}
				} else if (subtaskType == "min") {
					po.scr < cscore ? cscore = po.scr : 0;
					points.push_back(po);
					if (po.scr != 100) passed = false, info = po.info;
					if (po.scr == 0) {info = po.info; break;}
				} else if (subtaskType == "sum") {
					cscore += po.scr;
					points.push_back(po);
					if (po.scr != 100) passed = false, info = po.info;
				}
			}

			if (subtaskType == "packed") {
				tscore = scale_score(cscore, tfull);
			} else if (subtaskType == "min") {
				tscore = scale_score(cscore, tfull);
			} else if (subtaskType == "sum") {
				tscore = scale_score(cscore, (endI - startI + 1) * 100);
			}

			subtasks[t] = SubtaskInfo(passed, info, cscore);
			add_subtask_info(t, tscore, info, points);
		}
	}

	if (passed) tot_score = 100;
	if (conf_is("submit_answer", "on") || !passed) end_judge_ok();
	typedef decltype(PointInfo::ust) ust_t;
	typedef decltype(PointInfo::usm) usm_t;
	ust_t max_ex_time=-1;
	usm_t max_ex_mem=-1;
	for (int i = 1; i <= m; i++) {
		report_judge_status_f("Judging Extra Test #%d", i);
		PointInfo po = test_point("answer", -i);
		if (po.scr != 100) {
			po.num = -1;
			po.info = "Extra Test Failed : " + po.info + " on " + vtos(i);
			po.scr = -3;
			add_point_info(po);
			end_judge_ok();
		}
		if(po.ust!=ust_t(-1)&&(max_ex_time==ust_t(-1)||po.ust>max_ex_time))
			max_ex_time=po.ust;
		if(po.usm!=usm_t(-1)&&(max_ex_mem==usm_t(-1)||po.usm>max_ex_mem))
			max_ex_mem=po.usm;
	}
	if (m != 0) {
		PointInfo po(-1, 0, max_ex_time, max_ex_mem, "Extra Test Passed", "", "", "");
		add_point_info(po);
	}
	end_judge_ok();
}

void hack_test() {
	if (conf_is("submit_answer", "on")) {
		end_judge_judgement_failed("Hack is not supported in this problem.");
	} else {
		RunCompilerResult c_ret = !conf_is("with_implementer", "on") ? compile("answer") : compile_with_implementer("answer");
		if (!c_ret.succeeded) {
			end_judge_compile_error(c_ret);
		}
		TestPointConfig tpc;
		tpc.input_file_name = work_path + "/hack_input.txt";
		tpc.output_file_name = work_path + "/pro_output.txt";
		tpc.answer_file_name = work_path + "/std_output.txt";

		prepare_run_standard_program();
		PointInfo po = test_hack_point("answer", tpc);
		add_point_info(po);
		end_judge_ok();
	}
}

void sample_test() {
	if (conf_is("submit_answer", "on")) {
		int n = conf_int("n_tests", 10);
		for (int i = 1; i <= n; i++) {
			report_judge_status_f("Judging Test #%d", i);
			PointInfo po = test_point("answer", i);
			if (po.scr != 0) {
				po.info = "Accepted";
				po.scr = 100;
			}
			po.scr = scale_score(po.scr, conf_int("point_score", i, 100 / n));
			po.res = "no comment";
			add_point_info(po);
		}
		end_judge_ok();
	} else {
		report_judge_status_f("Compiling");
		RunCompilerResult c_ret = !conf_is("with_implementer", "on") ? compile("answer") : compile_with_implementer("answer");
		if (!c_ret.succeeded) {
			end_judge_compile_error(c_ret);
		}

		int n = conf_int("n_sample_tests", 0);
		bool passed = true;
		for (int i = 1; i <= n; i++) {
			report_judge_status_f("Judging Sample Test #%d", i);
			PointInfo po = test_point("answer", -i);
			po.num = i;
			if (po.scr != 100) {
				passed = false;
			}
			po.scr = scale_score(po.scr, 100 / n);
			add_point_info(po);
		}
		if (passed) {
			tot_score = 100;
		}
		end_judge_ok();
	}
}

void custom_test() {
	if (conf_is("submit_answer", "on")) {
		end_judge_judgement_failed("Custom test is not supported in this problem.");
	} else {
		report_judge_status_f("Compiling");
		RunCompilerResult c_ret = !conf_is("with_implementer", "on") ? compile("answer") : compile_with_implementer("answer");
		if (!c_ret.succeeded) {
			end_judge_compile_error(c_ret);
		}
		
		report_judge_status_f("Judging");
		add_custom_test_info(ordinary_custom_test("answer"));
		
		end_judge_ok();
	}
}

int main(int argc, char **argv) {
	judger_init(argc, argv);

	if (conf_is("test_new_hack_only", "on")) {
		hack_test();
	} else if (conf_is("test_sample_only", "on")) {
		sample_test();
	} else if (conf_is("custom_test", "on")) {
		custom_test();
	} else {
		ordinary_test();
	}
}
