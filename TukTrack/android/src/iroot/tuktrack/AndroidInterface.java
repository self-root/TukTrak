package org.iroot.tuktrack;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;

public class AndroidInterface {
    public static void dialNumber(Context context, String numberUri) {
        Intent dialIntent =  new Intent();
        dialIntent.setAction(Intent.ACTION_DIAL);
        dialIntent.setData(Uri.parse(numberUri));

        context.startActivity(dialIntent);
    }
}

