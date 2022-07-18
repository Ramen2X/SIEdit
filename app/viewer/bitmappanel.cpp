#include "bitmappanel.h"

#include <object.h>
#include <QBuffer>
#include <QGroupBox>

BitmapPanel::BitmapPanel(QWidget *parent)
{
  int row = 0;

  auto preview_grp = new QGroupBox(tr("Bitmap"));
  layout()->addWidget(preview_grp, row, 0, 1, 2);

  auto preview_layout = new QVBoxLayout(preview_grp);

  img_lbl_ = new QLabel();
  img_lbl_->setAlignment(Qt::AlignHCenter);
  preview_layout->addWidget(img_lbl_);

  desc_lbl_ = new QLabel();
  desc_lbl_->setAlignment(Qt::AlignHCenter);
  preview_layout->addWidget(desc_lbl_);

  FinishLayout();
}

void BitmapPanel::OnOpeningData(void *data)
{
  si::Object *o = static_cast<si::Object*>(data);
  si::bytearray d = o->ExtractToMemory();
  QByteArray b(d.data(), d.size());
  QBuffer read_buf(&b);
  QImage img;
  img.load(&read_buf, "BMP");

  img_lbl_->setPixmap(QPixmap::fromImage(img));

  desc_lbl_->setText(tr("%1x%2").arg(QString::number(img.width()), QString::number(img.height())));
}