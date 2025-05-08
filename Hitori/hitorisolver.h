#ifndef HITORISOLVER_H
#define HITORISOLVER_H
#include <QVector>

class HitoriSolver
{
public:
    HitoriSolver();
    static QVector<QVector<int>> GeneralAnswer;

    static bool PaintedProcessing(int n, QVector<QVector<int>>& answerField);
    static bool UnPaintedProcessing(int n, QVector<QVector<int>>& field, QVector<QVector<int>>& answerField);
    static int CountBFS(int n, int i, int j, QVector<QVector<int>> answerField);
    static bool DisconnectedFieldCheck(int n, int i, int j, QVector<QVector<int>> answerField);
    static bool DisconnectedProcessing(int n, QVector<QVector<int>>& answerField);
    static bool ThreeIndenticalProcessing(int n, QVector<QVector<int>>& field, QVector<QVector<int>>& answerField);
    static bool TwoIndenticalProcessing(int n, QVector<QVector<int>>& field, QVector<QVector<int>>& answerField);
    static bool BetweenIdentical(int n, QVector<QVector<int>>& field, QVector<QVector<int>>& answerField);
    static bool FieldProcessing(QVector<QVector<int>> field, QVector<QVector<int>>& answerField);
    static int CountRemainder(QVector<QVector<int>> curAnswer);
    static bool SolveHitori(QVector<QVector<int>> field, QVector<QVector<int>> answerField);
    static std::pair<bool, QVector<QVector<int>>> GetHitoriSolve(int n, QVector<QVector<int>> curHitori);
};

#endif // HITORISOLVER_H
