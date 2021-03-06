/****************************************************************************
**
** Copyright (C) 2018 Brian Hill
** All rights reserved.
**
** License Agreement
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** Software Author: Brian Hill <brian.hill@glowfish.ca>
**
** Summary: Header for the slide puzzle widget
**
****************************************************************************/

#ifndef SLIDE_PUZZLE_H
#define SLIDE_PUZZLE_H

#include "tile.h"

#include <QWidget>
#include <QtDesigner/QDesignerExportWidget>
#include <QGraphicsScene>

class QDESIGNER_WIDGET_EXPORT SlidePuzzle : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int rows READ rows WRITE setRows);
    Q_PROPERTY(int columns READ columns WRITE setColumns);
    Q_PROPERTY(QString image READ image WRITE setImage);
    Q_PROPERTY(QColor puzzleBackground READ puzzleBackground WRITE setPuzzleBackground);
    Q_PROPERTY(QColor imageBackground READ imageBackground WRITE setImageBackground);

public:
    explicit SlidePuzzle(QWidget *parent = 0);
    ~SlidePuzzle() {}

    /************************************************************************
    ** Encapsulated Properties
    ** - rows -- The number of rows to create.
    ** - columns -- The number of columns to create.
    ** - image -- The image file to use.
    ** - background -- The background color to use for the puzzle.
    ************************************************************************/
    int rows() const { return m_rows; }
    void setRows(int r);

    int columns() const { return m_columns; }
    void setColumns(int c);

    const QString &image() const { return m_imageFile; }
    void setImage(QString f);

    const QColor &puzzleBackground() const { return m_puzzleBackground; }
    void setPuzzleBackground(const QColor &c);

    const QColor &imageBackground() const { return m_imageBackground; }
    void setImageBackground(const QColor &c);

    bool solved() const { return m_solved; }

    QString describe() const;
    std::ostream &describe(std::ostream &strm) const;

protected:
    /************************************************************************
    ** Widget Callbacks
    ************************************************************************/
    void resizeEvent(QResizeEvent *);
    void showEvent(QShowEvent *);

private:
    /************************************************************************
    ** Internal Variables.
    ************************************************************************/
    int m_rows;
    int m_columns;
    QString m_imageFile;
    QColor m_puzzleBackground;
    QColor m_imageBackground;
    QGraphicsScene *m_scene;
    bool m_solved;

    template<typename C>
    void itemsByType(QList<C*> &o, int t) const {
        QList<QGraphicsItem*> items = m_scene->items(m_scene->sceneRect());
        for(QList<QGraphicsItem*>::const_iterator it(items.begin());
            it != items.end(); it++) {
            QGraphicsItem *item = *it;
            if (item->type() != t) continue;
            o.push_back(static_cast<C*>(item));
        }
    }

    void borders(QList<QGraphicsLineItem*> &l) const;
    void tiles(QList<Tile*> &t) const;
    QGraphicsRectItem *background() const;

    void setBorderColor(const QColor &c);
    void setEnabledTiles(bool e);

    bool populated() { return background() != NULL; }
    bool init(bool f);
    void fit();
    void setup();
    void reset();


public slots:
    void scramble();
    void validate();
    void enable();
    void disable();
    void pass();
};

#endif // SLIDE_PUZZLE_H
