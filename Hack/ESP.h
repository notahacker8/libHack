







NSSize get_window_size(const int window_index)
{
    __block NSSize size;
    dispatch_group_t group = dispatch_group_create();
    dispatch_group_enter(group);
    dispatch_group_async(group, dispatch_get_main_queue(), ^(void)
    {
        size = NSApp.windows[window_index].contentView.frame.size;
        dispatch_group_leave(group);
    });
    dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
    return size;
}

NSView* draw_blank_esp_box(NSView* parent_view)
{
    __block NSView* esp_box;
    dispatch_group_t group = dispatch_group_create();
    dispatch_group_enter(group);
    dispatch_async(dispatch_get_main_queue(), ^
    {
        esp_box = [[NSView alloc] init];
        esp_box.frame = NSMakeRect(0, 0, 0, 0);
        esp_box.wantsLayer = YES;
        esp_box.layer.borderColor = NSColor.orangeColor.CGColor;
        esp_box.layer.opacity = 1;
        esp_box.hidden = YES;
        esp_box.layer.cornerRadius = 3;
        esp_box.layer.borderWidth = 2;
        [parent_view addSubview:esp_box];
        dispatch_group_leave(group);
    });
    dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
    return esp_box;
}

NSTextField* draw_blank_esp_text(NSView* parent_view)
{
    __block NSTextField* tf;
    dispatch_group_t group = dispatch_group_create();
    dispatch_group_enter(group);
    dispatch_async(dispatch_get_main_queue(), ^
    {
        tf = [[NSTextField alloc] init];
        tf.frame = NSMakeRect(0, 0, 0, 0);
        tf.lineBreakMode = NSLineBreakByClipping;
        tf.editable = NO;
        tf.hidden = YES;
        tf.selectable = NO;
        tf.alignment = NSTextAlignmentCenter;
        tf.drawsBackground = NO;
        tf.bezeled = NO;
        tf.stringValue = @"";
        [tf setFont: [NSFont fontWithName:@"Menlo Regular" size:15]];
        tf.wantsLayer = YES;
        tf.textColor = NSColor.redColor;
        [parent_view addSubview:tf];
        dispatch_group_leave(group);
    });
    dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
    return tf;
}


void** allocate_blank_esp_box_array(NSView* parent_view,
                                    const int count)
{
    void** array = malloc(count * sizeof(void*));
    for (int i = 0 ; i < count ; i++)
    {
        array[i] = (__bridge void *)(draw_blank_esp_box(parent_view));
    }
    return array;
}

void** allocate_blank_esp_text_array(NSView* parent_view,
                                     const int count)
{
    void** array = malloc(count * sizeof(void*));
    for (int i = 0 ; i < count ; i++)
    {
        array[i] = (__bridge void *)(draw_blank_esp_text(parent_view));
    }
    return array;
}




void loop_refresh_esp_view_array(void** esp_view_array,
                                 const int start_index,
                                 const int count,
                                 const useconds_t wait_time)
{
    for (int i = start_index ; i < count ; i++)
    {
        dispatch_async(dispatch_get_main_queue(), ^
        {
            ((__bridge NSView*)esp_view_array[i]).hidden = YES;
        });
        usleep(wait_time);
    }
}


const bool is_valid_point(const NSPoint p)
{
    bool status = false;
    if (isnan(p.x) == false && isnan(p.y) == false)
    {
        if (isfinite(p.x) == true && isfinite(p.y) == true)
        {
            status = true;
        }
    }
    return status;
}


const bool mouse_is_in_bounds(const NSPoint mouse_pos,
                              const NSSize window_size)
{
    bool status = false;
    if (mouse_pos.x < window_size.width && mouse_pos.x > 0)
    {
        if (mouse_pos.y < window_size.height && mouse_pos.y > 0)
        {
            status = true;
        }
    }
    return status;
}

