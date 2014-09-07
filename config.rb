##
## Compass config.rb
##

# Location of the theme's resources.
css_dir = "css"
sass_dir = "sass"
images_dir = "images"
generated_images_dir = images_dir + "/generated"
javascripts_dir = "js"

# Require any additional compass plugins installed on your system.
require 'compass-normalize'
require 'rgbapng'
require 'toolkit'
require 'sass-globbing'

##
## Compiled config
##
output_style = :expanded
relative_assets = true
line_comments = false
add_import_path 'sass'
