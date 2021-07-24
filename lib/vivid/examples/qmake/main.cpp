#include "vivid/vivid.h"

#include <glm/gtc/random.hpp>

#include <QImage>
#include <QColor>
#include <QDir>

#include <iostream>
#include <functional>
#include <sstream>
#include <fstream>


int main( int, char* argv[] )
{
    using namespace vivid;

    QDir dir( argv[ 0 ] );
    dir.cdUp();
    dir.mkdir( "out/" );
    dir.cd( "out/" );

    //  introduction

    ColorMap hslMap( ColorMap::Preset::Hsl );
    std::cout << ansi::colorize( "vivid", hslMap ) << std::endl;

    //  escape codes

    std::cout << "\n";
    ansi::printColorTable();

    std::cout << "\n";
    ansi::printColorPresets();

    //  colormaps

    dir.mkpath( "colormaps/" );
    dir.cd( "colormaps/" );

    std::vector<ColorMap::Preset> presets = {
        ColorMap::Preset::BlueYellow,
        ColorMap::Preset::CoolWarm,
        ColorMap::Preset::Hsl,
        ColorMap::Preset::HslPastel,
        ColorMap::Preset::Inferno,
        ColorMap::Preset::Magma,
        ColorMap::Preset::Plasma,
        ColorMap::Preset::Rainbow,
        ColorMap::Preset::Turbo,
        ColorMap::Preset::Viridis,
        ColorMap::Preset::Vivid
    };

    std::cout << "\n";

    for ( const auto& preset : presets )
    {
        std::cout << "Exporting " << ColorMap::nameForPreset( preset ) << " ..." << std::endl;

        ColorMap cmap( preset );
        cmap.interpolation = ColorMap::Interpolation::Lch;
        QImage img( 512, 32, QImage::Format_RGB32 );

        for ( int c = 0; c < img.width(); c++ )
        {
            const float t = c / ( img.width() - 1.f );
            const auto col = cmap.at( t );
            const QColor qcol = QColor::fromRgbF( col.x, col.y, col.z );

            for ( int r = 0; r < img.height(); r++ ) {
                img.setPixelColor( c, r, qcol );
            }
        }

        img.save( dir.filePath( QString::fromStdString( ColorMap::nameForPreset( preset ) + ".png" ) ));
    }

    //  interpolation

    dir.cdUp();
    dir.mkdir( "interpolations/" );
    dir.cd( "interpolations/" );

    using lerp_t = std::function< Color( const Color&, const Color&, const float ) >;
    using alerp_t = std::pair<lerp_t, std::string>; //  annotated lerp function
    auto lerpHslClamp = []( const Color& c1, const Color& c2, const float t ) -> Color {
        return rgb::clamp( rgb_t( lerpHsl( c1, c2, t ).value() ) );
    };

    const std::vector<alerp_t> lerps = {
        { lerpRgb, "lerpRgb" },
        { lerpHsv, "lerpHsv" },
        { lerpHsl, "lerpHsl" },
        { lerpLch, "lerpLch" },
        { lerpHslClamp, "lerpHslClamped" }
    };

    static const rgb_t c1( 0.7f, 0.3f, 0.3f );
    static const rgb_t c2( 0.1f, 0.6f, 0.4f );

    std::cout << "\n";

    for ( const auto& lerp: lerps )
    {
        std::cout << "Exporting " << lerp.second << " ..." << std::endl;
        QImage img( 512, 32, QImage::Format_RGB32 );

        for ( int c = 0; c < img.width(); c++ )
        {
            const float t = c / ( img.width() - 1.f );
            const auto col = glm::vec<3, double>( lerp.first( c1, c2, t ).value() );
            const QColor qcol = QColor::fromRgbF( col.x, col.y, col.z );

            for ( int r = 0; r < img.height(); r++ ) {
                img.setPixelColor( c, r, qcol );
            }
        }

        img.save( dir.filePath( QString::fromStdString( lerp.second + ".png" ) ));
    }

    //  low-level conversions

    static const rgb_t col( 1.f, 0.7f, 0.5f );
    const hsl_t hsl = hsl::fromRgb( rgb_t( col ) );
    const rgb_t rgb_2 = rgb::fromHsl( hsl );

    std::cout << "\n";
    std::cout << col << " -> " << hsl << " -> " << rgb_2 << std::endl;

    //  high-level conversions

    Color color = { 255, 123, 0 };

    std::cout << color.hsl() << std::endl;
    std::cout << lerpHsl( color, c2, 0.5f ) << std::endl;   //  implicit Color() construction from c2
    std::cout << "\n";

    srand( uint32_t( time( nullptr ) ));

    for ( size_t i = 0; i < 10; i++ ) {
        Color col( glm::linearRand( col_t( 0 ), col_t( 1 ) ), Color::Space::Rgb );
        std::cout << col.quickInfo() << "\n";
    }

    for ( size_t i = 0; i < 3; i++ ) {
        std::cout << "\n";
        Color col( glm::linearRand( col_t( 0 ), col_t( 1 ) ), Color::Space::Rgb );
        std::cout << col.info() << "\n";
    }

    //  lossy conversion

    Color original( "#a1b2c3" );
    Color lossy = original.index();

    std::cout << "\n";
    std::cout << "original: " << original.quickInfo() << "\n";
    std::cout << "lossy:    " << lossy.quickInfo() << "\n";

    //  encoding

    std::cout << "\n";
    std::cout << ansi::fg( 9 ) << "yay colors" << ansi::reset << std::endl;
    std::cout << html::fg( "#abc123" ) << "hex hex!" << html::close << std::endl;
    std::cout << html::fg( col8_t( 100, 144, 159 ) ) << "html, aw yes" << html::close << std::endl;

    //  wide gamut conversions

    adobe_t adobe = { 1, 0, 0 };
    srgb_t srgb = { 1, 0, 0 };

    std::cout << "\n";
    std::cout << adobe::fromSrgb( srgb::fromAdobe( adobe ) ) << std::endl;
    std::cout << srgb::fromAdobe( adobe::fromSrgb( srgb ) ) << std::endl;

    //  rainbow text

    ColorMap rainbowMap( ColorMap::Preset::Rainbow );
    const std::string text = "How can you tell? - Raaaaaaiiiinbooooooowwws.";

    std::cout << "\n";
    std::cout << ansi::colorize( text, rainbowMap ) << std::endl;

    return EXIT_SUCCESS;
}
