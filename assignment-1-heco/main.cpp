//Name: Zihan Li
//Student# : A01282005

#include "matrix.hpp"

int main() {
    int mRow;
    int mCol;
    double d[100];
    double *ptrD=d;
//    mRow=ReadFile(ptrD);
//    mCol=mRow;
    Matrix m(ptrD);
    mRow=m.GetRowCount();
    mCol=m.GetColumnCount();
//    m.arrToM(ptrD);
//    m.PrintMatrix();
    Matrix q(mRow,mCol);
    m.GetSMatrix();
//    m.PrintMatrix();
    q.GetQMatrix();
//    q.PrintMatrix();
    Matrix rank(mRow,1);
    rank.GetRank();
//    rank.PrintMatrix();
    //M = 0.85 * S + (1 - 0.85) * Q
    m+=q;
//    m.PrintMatrix();
    Matrix m_tmp,rank_old;
    m_tmp=m;
    rank_old=rank;
    rank=(m*=rank);
//    rank.PrintMatrix();
    while (!(rank_old==rank)){
        rank_old=rank;
        m=m_tmp;
        rank=(m*=rank);
    }
//    rank.PrintMatrix();
    rank.ShowRank();
    return 0;
}
