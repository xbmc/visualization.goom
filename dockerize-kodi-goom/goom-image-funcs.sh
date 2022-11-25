function get_kodi_goom_image_name()
{
    local -r kodi_image_os_type="$1"
    local -r kodi_image_os_tag="$2"
    local -r kodi_version="$3"

    echo "kodi-goom/${kodi_image_os_type}-${kodi_image_os_tag}:${kodi_version}"
}
