#include <thread>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <cmath>
#include <mutex>
#include <atomic>

class BlockMultiplyMatrix{
private:
    std::vector<std::vector<double>> A, B, C;
    int sizeMatrix;
    int blockSize;
    int blocksOnLine;
    std::mutex indexMutex;

    void mFillMatrix(){
        srand(time(0));
        for (int i = 0; i < sizeMatrix; i++){
            for (int j = 0; j < sizeMatrix; j++){
                A[i][j] = ((double)rand()) / RAND_MAX;
                B[i][j] = ((double)rand()) / RAND_MAX;
                C[i][j] = 0;
            }
        }
    }

    void mPrintMatrix(const std::vector<std::vector<double>>& matrix){
        for (auto arr: matrix){
            for (double element: arr){
                std::cout << std::setprecision(2) << element << '\t';
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::vector<double>> mBaseMultiply(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B){
        int n = A[0].size();
        
        int rowCount = A.size();
        int columnCount = B[0].size();
        std::vector<std::vector<double>> result(rowCount, std::vector<double>(columnCount));
        for (int i = 0; i < rowCount; i++){
            for (int j = 0; j < columnCount; j++){
                double sum = 0;
                for (int x = 0; x < n; x++){
                    sum += A[i][x] * B[x][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    void mSumMatrix(std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B){
        for (int i = 0; i < A.size(); i++){
            for (int j = 0; j < A[i].size(); j++){
                A[i][j] += B[i][j];
            }
        }
    }

    std::vector<std::vector<double>> mGetMatrixBlock(const std::vector<std::vector<double>>& matrix, int startX, int endX, int startY, int endY){
        std::vector<std::vector<double>> result(endY - startY, std::vector<double>(endX - startX));
        for (int y = startY; y < endY; y++){
            for (int x = startX; x < endX; x++){
                result[y - startY][x - startX] = matrix[y][x];
            }
        }
        return result;
    }

    std::vector<std::vector<double>> mGetBlockByIndex(const std::vector<std::vector<double>>& matrix, int y, int x, int rowsPerBlock, int columnsPerBlock){
        return mGetMatrixBlock(matrix, columnsPerBlock * x, columnsPerBlock * (x + 1), rowsPerBlock * y, rowsPerBlock * (y + 1));
    }

    void mGetNextBlockIndex(int& blockX, int& blockY, int blocksOnLine) {        
        blockX++;
        if (blockX >= blocksOnLine) {
            blockX = 0;
            blockY++;
        }
    }

    void mFillC(int blockX, int blockY, int blocksPerThread, const std::vector<std::vector<double>>& C_block){
        for (int i = blockY * blockSize; i < (blockY + 1) * blockSize; i++){
            for (int j = blockX * blockSize; j < (blockX + 1) * blockSize; j++){
                C[i][j] = C_block[i - blockY * blockSize][j - blockX * blockSize];
            }
        }
    }

public:
    BlockMultiplyMatrix(int sizeMatrix, int blockSize): sizeMatrix(sizeMatrix), blockSize(blockSize){
        A.resize(sizeMatrix, std::vector<double>(sizeMatrix));
        B.resize(sizeMatrix, std::vector<double>(sizeMatrix));
        C.resize(sizeMatrix, std::vector<double>(sizeMatrix));

        mFillMatrix();
        blocksOnLine = sizeMatrix / blockSize;
    }

    std::vector<std::vector<double>> baseMultiply(){
        return mBaseMultiply(A, B);
    }

    void parallelMultiply(int threadsCount){
        std::vector<std::thread> threadArr;
        
        int blocksPerThread = blocksOnLine * blocksOnLine / threadsCount;
        //int extraBlocks = blocksOnLine * blocksOnLine % threadsCount;

        //int indexThread = 0;
        for (int i = 0; i < threadsCount * blocksPerThread; i += blocksPerThread){
            threadArr.emplace_back([this, blocksPerThread, i](){
                int blockX = i % blocksOnLine;
                int blockY = i / blocksOnLine;
                //std::cout << blockY << " - " << blockX << " BLOCKS_PER_THREAD: " << blocksPerThread <<std::endl;
                for (int j = 0; j < blocksPerThread; j++){
                    std::vector<std::vector<double>> C_block (blockSize, std::vector<double>(blockSize, 0));
                    for (int t = 0; t < blocksOnLine; t++){
                        auto A_block = mGetBlockByIndex(A, blockX, t, blockSize, blockSize);
                        auto B_block = mGetBlockByIndex(B, t, blockY, blockSize, blockSize);
                        mSumMatrix(C_block, mBaseMultiply(A_block, B_block));
                    }
                    
                    //std::cout << blockY << " " << blockX << std::endl;
                    mFillC(blockX, blockY, blocksPerThread, C_block);
                    mGetNextBlockIndex(blockX, blockY, blocksOnLine);
                }
            });
            //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            //indexThread++;
        }
        
        for (auto& th: threadArr){
            th.join();
        }
        //std::cout << currentBlockY << " " << currentBlockX << std::endl;
    }
};