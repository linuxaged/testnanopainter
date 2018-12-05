#ifndef PAGE_H
#define PAGE_H

#include <QQuickItem>
#include "../libqnanopainter/qnanoquickitem.h"
#include "../libqnanopainter/qnanoquickitempainter.h"

struct Stroke {
    Stroke() {
        color = Qt::black;
        weight = 4;
    }
    QColor color;
    int weight;
};
struct Line {
    QColor color;
    int weight;
    bool erase;
    std::vector<QPoint> points;
};
using Lines = std::vector<Line>;

class PagePainter : public QNanoQuickItemPainter
{
public:
    PagePainter(const Lines& lines) : m_lines(lines)
    {
    }
    void paint(QNanoPainter *p) override
    {
        if (m_lines.empty())
            return;

        for (auto& line : m_lines) {
            if (!line.erase)
            {
                p->beginPath();
                p->setMiterLimit(15.0f);
                p->setLineJoin(QNanoPainter::JOIN_ROUND);
                p->setLineCap(QNanoPainter::CAP_ROUND);
                p->setStrokeStyle(QNanoColor::fromQColor(line.color));
                p->setLineWidth(line.weight);
                for (size_t n = 0; n < line.points.size(); ++n) {
                    if (0 == n) {
                        p->moveTo(line.points[0]);
                    } else {
                        p->lineTo(line.points[n]);
                    }
                }
                p->stroke();
            }
            else {
                p->setStrokeStyle(QNanoColor(255,255,255,0));
                p->beginPath();
                for (auto& e : line.points) {
                    p->fillRect(static_cast<float>(e.x() - 16.0), static_cast<float>(e.y() - 16.0), 32, 32);
                }
            }

        }

    }
private:
    const Lines& m_lines;
};

class Page : public QNanoQuickItem
{
    Q_OBJECT
public:
    Page();

signals:

public slots:
};

#endif // PAGE_H
