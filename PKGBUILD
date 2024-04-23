# Maintainer: Martin Filion <mordillo98@gmail.com>
pkgname=flash_eol_app
pkgver=1
pkgrel=1
pkgdesc="Displays that Adobe Flash is EOL"
url="https://github.com/Mordillo98/flash_eol_app"
arch=('any')
license=('MIT')
provides=($pkgname)
conflicts=($pkgname)
source=('git+https://github.com/Mordillo98/flash_eol_app.git')
depends=('gtk3')
makedepends=('gcc')
md5sums=('SKIP')

build() {
cd "${srcdir}/${pkgname}"
gcc `pkg-config --cflags gtk+-3.0` -o flash_eol_app flash_eol_app.c `pkg-config --libs gtk+-3.0` -std=c11
}

package() {
  install -d /$pkgdir/usr
  install -d /$pkgdir/opt/archbangretro/${pkgname}

  cp -R $pkgname/share /$pkgdir/usr/
  cp $pkgname/$pkgname /$pkgdir/opt/archbangretro/${pkgname}
  cp $pkgname/FLASH-PLAYER-DEAD.png /$pkgdir/opt/archbangretro/${pkgname}
}