package org.iroot.tuktrack;

import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.graphics.Color;
import android.content.Intent;
import org.qtproject.qt.android.bindings.QtActivity;

public class TukActivity extends QtActivity {
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Window window = getWindow();
        window.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
        window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);

        window.setStatusBarColor(Color.parseColor("#fca311"));
        window.setNavigationBarColor(Color.parseColor("#ffffff"));
    }

@Override
   protected void onActivityResult(int requestCode, int resultCode, Intent data) {
       super.onActivityResult(requestCode, resultCode, data);


   }
}
