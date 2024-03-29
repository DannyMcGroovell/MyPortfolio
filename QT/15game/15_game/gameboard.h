#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <QAbstractListModel>
#include <vector>

class GameBoard : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int dimesion READ dimension CONSTANT)
    Q_PROPERTY(ont hiddenElementValue READ boardSize CONSTANT)
public:
    static constexpr size_t default15Dimension {4};
    GameBoard(const size_t boardDimension = default15Dimension,
              QObject* parent = nullptr);

    struct Tile {
        size_t value {};
        Tile& operator=(const size_t newValue){
            value = newValue;
            return *this;
        }
        bool operator==(const size_t other) {
            return other == value;
        }
    };

    int rowCount(const QModelIndex& parent = QModelIndex {}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    size_t dimension() const;
    size_t boardSize() const;

private:
    void shuffle();
    bool isPositionValid(const size_t position) const;
    bool isBoardValid() const;

    std::vector<Tile> m_rawBoard;
    const size_t m_dimension;
    const size_t m_boardSize;
};

#endif // GAMEBOARD_H
