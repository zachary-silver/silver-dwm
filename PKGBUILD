# Maintainer:  Zachary Silver <zmansilver@gmail.com>

pkgname=silver-dwm
pkgver=6.1
pkgrel=4
pkgdesc="A customized clone of a dynamic window manager for X"
url="https://github.com/ZmanSilver/silver-dwm"
arch=('i686' 'x86_64')
license=('MIT')
options=(zipman)
depends=('libx11' 'libxinerama' 'libxft' 'freetype2' 'silver-st' 'dmenu' 'ttf-font-awesome')
install=dwm.install
source=(https://www.dropbox.com/s/5cu3zf60q27l05u/silver-dwm.tar.gz
	config.h
	dwm.desktop)
md5sums=('3414b14b64557b2b7d786244e89425d1'
         'b2a40545589193ebb1c371169d10d42e'
         '7f873efd596b8b30e2cdc09583209874')

prepare() {
  cd $srcdir/$pkgname
  cp $srcdir/config.h config.h
}

build() {
  cd $srcdir/$pkgname
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  cd $srcdir/$pkgname
  make PREFIX=/usr DESTDIR=$pkgdir install
  install -m644 -D LICENSE $pkgdir/usr/share/licenses/$pkgname/LICENSE
  install -m644 -D README $pkgdir/usr/share/doc/$pkgname/README
  install -m644 -D $srcdir/dwm.desktop $pkgdir/usr/share/xsessions/dwm.desktop
}
