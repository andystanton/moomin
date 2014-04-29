include Math

$pi = 3.1415927

def get_coord_pair(x, y, is_float)
    "#{x.round(2)}#{is_float ? 'f' : ''}, #{y.round(2)}#{is_float ? 'f' : ''}"
end

def print_triangle_fan(num_segments, radius, is_float)
    segment_angle = 360/num_segments

    puts "// triangle fan"
    puts "{"
    puts "  0.0, 0.0,"
    puts "  #{get_coord_pair(0, 0, is_float)},"

    for segment in -1..num_segments-1
        angle = segment * segment_angle

        x = Math::sin(angle * $pi / 180) * radius
        y = Math::cos(angle * $pi / 180) * radius

        coord    = "#{get_coord_pair(x, y, is_float)}"
        end_line = "#{segment == num_segments-1 ? '' : ','}"

        puts "  #{coord}#{end_line}"
    end

    puts "};"
end

def print_triangle_strip(num_segments, radius, is_float)
    segment_angle = 360/num_segments

    puts "// triangle strip"
    puts "{"

    for segment in 0..num_segments-1
        angle      = segment_angle * segment
        next_angle = segment_angle * (segment + 1)

        x      = radius * Math::sin(angle      * $pi / 180)
        y      = radius * Math::cos(angle      * $pi / 180)
        next_x = radius * Math::sin(next_angle * $pi / 180)
        next_y = radius * Math::cos(next_angle * $pi / 180)

        centre_coord = get_coord_pair(     0,      0, is_float)
        first_coord  = get_coord_pair(     x,      y, is_float)
        second_coord = get_coord_pair(next_x, next_y, is_float)

        end_line = "#{segment == num_segments-1 ? '' : ','}"

        puts "  #{centre_coord},  #{first_coord},  #{second_coord}#{end_line}"

    end

    puts "};"
end

print_triangle_fan(36, 10, true)
print_triangle_strip(36, 10, true)