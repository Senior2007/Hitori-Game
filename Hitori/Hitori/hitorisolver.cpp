#include "hitorisolver.h"
#include <queue>

HitoriSolver::HitoriSolver() {}

QVector<QVector<int>> HitoriSolver::GeneralAnswer = {};

bool HitoriSolver::PaintedProcessing(int n, QVector<QVector<int>>& answerField) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (answerField[i][j] == 1) {
                if (i > 0) {
                    if (answerField[i - 1][j] == 1) return 0;
                    answerField[i - 1][j] = 0;
                }
                if (j > 0) {
                    if (answerField[i][j - 1] == 1) return 0;
                    answerField[i][j - 1] = 0;
                }
                if (i < n - 1) {
                    if (answerField[i + 1][j] == 1) return 0;
                    answerField[i + 1][j] = 0;
                }
                if (j < n - 1) {
                    if (answerField[i][j + 1] == 1) return 0;
                    answerField[i][j + 1] = 0;
                }
            }
        }
    }

    return 1;
}

bool HitoriSolver::UnPaintedProcessing(int n, QVector<QVector<int>>& field, QVector<QVector<int>>& answerField) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (answerField[i][j] == 0) {
                for (int k = 0; k < n; k++) {
                    if (k != i && field[k][j] == field[i][j]) {
                        if (answerField[k][j] == 0) return 0;
                        answerField[k][j] = 1;
                    }
                    if (k != j && field[i][k] == field[i][j]) {
                        if (answerField[i][k] == 0) return 0;
                        answerField[i][k] = 1;
                    }
                }
            }
        }
    }

    return 1;
}

int HitoriSolver::CountBFS(int n, int i, int j, QVector<QVector<int>> answerField) {
    bool used[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            used[i][j] = 0;
        }
    }

    std::queue<int> X, Y;
    X.push(i);
    Y.push(j);
    used[i][j] = 1;

    int answer = 0;
    int steps[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while(!X.empty()) {
        answer++;
        int curX = X.front(); X.pop();
        int curY = Y.front(); Y.pop();

        for (int i = 0; i < 4; i++) {
            int newX = curX + steps[i][0];
            int newY = curY + steps[i][1];

            if (newX >= 0 && newY >= 0 && newX < n && newY < n && !used[newX][newY] && answerField[newX][newY] != 1) {
                X.push(newX);
                Y.push(newY);
                used[newX][newY] = 1;
            }
        }
    }

    return answer;
}

bool HitoriSolver::DisconnectedFieldCheck(int n, int i, int j, QVector<QVector<int>> answerField) {
    answerField[i][j] = 1;
    int ci = -1, cj = -1, cnt = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (answerField[i][j] != 1) {
                cnt++;
                ci = i;
                cj = j;
            }
        }
    }

    return (CountBFS(n, ci, cj, answerField) != cnt);
}

bool HitoriSolver::DisconnectedProcessing(int n, QVector<QVector<int>>& answerField) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (answerField[i][j] == 2) {
                if (DisconnectedFieldCheck(n, i, j, answerField)) {
                    answerField[i][j] = 0;
                }
            }
        }
    }

    int cnt = 0, curI = -1, curJ = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (answerField[i][j] != 1) {
                cnt++;
                curI = i;
                curJ = j;
            }
        }
    }

    return (cnt == CountBFS(n, curI, curJ, answerField));
}

bool HitoriSolver::ThreeIndenticalProcessing(int n, QVector<QVector<int>>& field, QVector<QVector<int>>& answerField) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0 && i < n - 1) {
                if (field[i - 1][j] == field[i][j] && field[i][j] == field[i + 1][j]) {
                    if (answerField[i][j] == 1) return 0;
                    answerField[i][j] = 0;
                }
            }

            if (j > 0 && j < n - 1) {
                if (field[i][j - 1] == field[i][j] && field[i][j] == field[i][j + 1]) {
                    if (answerField[i][j] == 1) return 0;
                    answerField[i][j] = 0;
                }
            }
        }
    }

    return 1;
}

bool HitoriSolver::TwoIndenticalProcessing(int n, QVector<QVector<int>>& field, QVector<QVector<int>>& answerField) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0 && field[i][j] == field[i - 1][j]) {
                for (int k = 0; k < n; k++) {
                    if (k == i || k == i - 1) continue;
                    if (field[k][j] == field[i][j]) {
                        if (answerField[k][j] == 0) return 0;
                        answerField[k][j] = 1;
                    }
                }
            }

            if (j > 0 && field[i][j] == field[i][j - 1]) {
                for (int k = 0; k < n; k++) {
                    if (k == j || k == j - 1) continue;
                    if (field[i][k] == field[i][j]) {
                        if (answerField[i][k] == 0)  return 0;
                        answerField[i][k] = 1;
                    }
                }
            }
        }
    }

    return 1;
}

bool HitoriSolver::BetweenIdentical(int n, QVector<QVector<int>>& field, QVector<QVector<int>>& answerField) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0 && i < n - 1) {
                if (field[i - 1][j] == field[i + 1][j]) {
                    if (answerField[i][j] == 1) return 0;
                    answerField[i][j] = 0;
                }
            }

            if (j > 0 && j < n - 1) {
                if (field[i][j - 1] == field[i][j + 1]) {
                    if (answerField[i][j] == 1) return 0;
                    answerField[i][j] = 0;
                }
            }
        }
    }

    return 1;
}

bool HitoriSolver::FieldProcessing(QVector<QVector<int>> field, QVector<QVector<int>>& answerField) {
    int n = field.size();
    QVector<QVector<int>> newField = answerField;

    while(1) {
        if (!PaintedProcessing(n, newField)) return 0;
        if (!UnPaintedProcessing(n, field, newField)) return 0;
        if (!DisconnectedProcessing(n, newField)) return 0;
        if (!ThreeIndenticalProcessing(n, field, newField)) return 0;
        if (!TwoIndenticalProcessing(n, field, newField)) return 0;
        if (!BetweenIdentical(n, field, newField)) return 0;

        if (newField == answerField) break;
        answerField = newField;
    }

    return 1;
}

int HitoriSolver::CountRemainder(QVector<QVector<int>> curAnswer) {
    int cnt = 0;
    for (auto u : curAnswer) {
        for (auto v : u) {
            cnt += (v == 2);
        }
    }

    return cnt;
}

bool HitoriSolver::SolveHitori(QVector<QVector<int>> field, QVector<QVector<int>> answerField) {
    if (!FieldProcessing(field, answerField)) {
        return 0;
    }

    if (CountRemainder(answerField) == 0) {
        GeneralAnswer = answerField;
        return 1;
    }

    int n = field.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (answerField[i][j] == 2) {
                answerField[i][j] = 1;
                if (SolveHitori(field, answerField)) {
                    return 1;
                }

                answerField[i][j] = 0;
                if (SolveHitori(field, answerField)) {
                    return 1;
                }

                answerField[i][j] = 2;
            }
        }
    }

    return 0;
}

std::pair<bool, QVector<QVector<int>>> HitoriSolver::GetHitoriSolve(int n, QVector<QVector<int>> curHitori) {
    GeneralAnswer.clear();

    QVector<QVector<int>> curAnswer;

    for (int i = 0; i < n; i++) {
        QVector<int> v;
        for (int j = 0; j < n; j++) {
            v.push_back(2);
        }
        curAnswer.push_back(v);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool pr = 0;
            for (int k = 0; k < n; k++) {
                if (k != i) {
                    if (curHitori[i][j] == curHitori[k][j]) {
                        pr = 1;
                    }
                }

                if (k != j) {
                    if (curHitori[i][j] == curHitori[i][k]) {
                        pr = 1;
                    }
                }
            }

            if (!pr) {
                curAnswer[i][j] = 0;
            }
        }
    }

    bool answer = SolveHitori(curHitori, curAnswer);
    return {answer, GeneralAnswer};
}
