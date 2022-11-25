#define CATCH_CONFIG_RUNNER
#include "closest_pair.h"
#include "../catch.hpp"
#include <ctime>
#include <random>
#include "math.h"
#include <stdexcept>
#include <algorithm>

using namespace std;

double distance(Point P1, Point P2) {
	return sqrt(pow((P1.x - P2.x), 2) + pow((P1.y - P2.y), 2));
}

std::pair<Point, Point> Naiv(const std::vector<Point>& points) {

	//наивный алгоритм (перебор)
	int i = 0, j = 1, mini = i, minj = j;
	double min = distance(points[i], points[j]), dis;
	for (i = 0; i < points.size() - 1; i++)
		for (j = i + 1; j < points.size(); j++) {
			dis = distance(points[i], points[j]);
			if (dis < min) {
				min = dis;
				mini = i;
				minj = j;
			}
		}
	return std::make_pair(Point(points[mini]), Point(points[minj]));
}

bool comp(Point a, Point b) {
	return a.y < b.y;
}

std::pair<Point, Point> closest_pair_between(const std::vector<Point>& PLeft, const std::vector<Point>& PRight, double d) {
	double Xm = (PLeft[PLeft.size() - 1].x + PRight[0].x) / 2;
	int i, j = 1;
	std::vector<Point> PStripe;
	for (i = 0; i < PLeft.size(); i++)
		if (abs(PLeft[i].x - Xm) < d) PStripe.push_back(PLeft[i]);
	for (i = 0; i < PRight.size(); i++)
		if (abs(PRight[i].x - Xm) < d) PStripe.push_back(PRight[i]);
	if (PStripe.size() < 2) return std::make_pair(PLeft[0], PRight[0]);
	std::sort(PStripe.begin(), PStripe.end(), comp);

	double ymin = distance(PStripe[0], PStripe[1]);
	int mini = 0, minj = 1;
	for (i = 0; i < PStripe.size(); i++)
		for (j = i + 1; (j < PStripe.size()) && (abs(PStripe[i].y - PStripe[j].y) < d); j++)
			if (ymin > distance(PStripe[i], PStripe[j])) {
				ymin = distance(PStripe[i], PStripe[j]);
				mini = i;
				minj = j;
			}
	return std::make_pair(PStripe[mini], PStripe[minj]);
}

std::pair<Point, Point> Separate(const std::vector<Point>& points) {
	if (points.size() == 1) {
		Point Max_left(-1000, -1000);
		Point Max_right(1000, 1000);
		return std::make_pair(Max_left, Max_right);
	}
	if (points.size() < 4) return Naiv(points);
	else {
		int i, j;
		double sumX = 0;
		for (i = 0; i < points.size(); i++)
			sumX += points[i].x;
		sumX /= points.size();
		std::vector<Point> SepLeft;
		std::vector<Point> SepRight;
		std::vector<Point> SepEdge;
		for (i = 0; i < points.size(); i++)
			if (points[i].x < sumX) SepLeft.push_back(points[i]);
			else if (points[i].x > sumX) SepRight.push_back(points[i]);
			else SepEdge.push_back(points[i]);
		if (SepEdge.size() > 0) {
			for (i = 0; i < SepEdge.size() / 2; i++)
				SepLeft.push_back(SepEdge[i]);
			for (j = i; j < SepEdge.size(); j++)
				SepRight.push_back(SepEdge[j]);
		}

		std::pair<Point, Point> pl = Separate(SepLeft);
		std::pair<Point, Point> pr = Separate(SepRight);
		double d = distance(pl.first, pl.second);
		if (d > distance(pr.first, pr.second))
			d = distance(pr.first, pr.second);

		std::pair<Point, Point> pb = closest_pair_between(SepLeft, SepRight, d);
		if ((distance(pb.first, pb.second) < distance(pl.first, pl.second)) && (distance(pb.first, pb.second) < distance(pr.first, pr.second))) return pb;
		else if (distance(pl.first, pl.second) < distance(pr.first, pr.second)) return pl;
		else return pr;
	}
}

int main(int argc, char** argv) {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(-1000, 1000);
    setlocale(LC_ALL, "Russian");
    int N, i;
    cout << "Введите количество точек: ";
    cin >> N;
    std::vector<Point> points;
    for (i = 0; i < N; i++) {
        Point P(distribution(generator), distribution(generator));
        points.push_back(P);
    }

    std::pair<Point, Point> Pa;
    auto t1 = chrono::high_resolution_clock::now();
    Pa = Naiv(points);
    auto t2 = chrono::high_resolution_clock::now();
    auto seconds = chrono::duration<double>(t2 - t1).count();
    std::cout << "\nПоиск по " << N << " точкам наивным перебором занял " << fixed << seconds << " секунд\n";

    t1 = chrono::high_resolution_clock::now();
    Pa = Separate(points);
    t2 = chrono::high_resolution_clock::now();
    seconds = chrono::duration<double>(t2 - t1).count();
    std::cout << "Поиск по " << N << " точкам алгоритмом 'разделяй и влавствуй' занял " << fixed << seconds << " секунд\n";

    int result = Catch::Session().run(argc, argv);
    return result;
}