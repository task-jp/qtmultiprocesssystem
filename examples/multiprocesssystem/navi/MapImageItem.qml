import QtQuick 2.5;
import QtLocation 5.6

MapQuickItem {
    id: root

    property int align: Item.Center
    property int radius: 128

    anchorPoint.x: {
        switch (root.align) {
        case Item.TopLeft:
        case Item.Left:
        case Item.BottomLeft:
            return 0;
        case Item.Top:
        case Item.Center:
        case Item.Bottom:
            return image.width / 2
        case Item.TopRight:
        case Item.Right:
        case Item.BottomRight:
            return image.width;
        }
    }

    anchorPoint.y: {
        switch (root.align) {
        case Item.TopLeft:
        case Item.Top:
        case Item.TopRight:
            return 0;
        case Item.Left:
        case Item.Center:
        case Item.Right:
            return image.height / 2
        case Item.BottomRight:
        case Item.BottomLeft:
        case Item.Bottom:
            return image.height;
        }
    }

    property alias source: image.source
    sourceItem: Image {
        id: image
        width: sourceSize.width / Math.max(sourceSize.width, sourceSize.height) * root.radius
        height: sourceSize.height / Math.max(sourceSize.width, sourceSize.height) * root.radius
    }
}
