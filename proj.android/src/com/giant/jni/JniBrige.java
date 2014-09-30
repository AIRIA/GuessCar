package com.giant.jni;

import org.json.JSONException;
import org.json.JSONObject;

import y.u.w.br.Ywaj;
import y.u.w.br.Ywam;
import y.u.w.st.Ywbv;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.util.Log;
import android.view.Gravity;
import android.widget.FrameLayout;

import com.giant.net.NetManager;

public class JniBrige {

	public native void exitGame();

	static public JniBrige _instance;
	public Activity context;
	private boolean showAds = false;

	public static Object getObject() {
		return getInstance();
	}

	public static JniBrige getInstance() {
		if (_instance == null) {
			_instance = new JniBrige();
		}
		return _instance;
	}

	public void init(Context context) {
		this.context = (Activity) context;
		try {
			String adsSetting = NetManager
					.sendHttpRequest("https://gist.githubusercontent.com/AIRIA/6f0906e11d40a6d1c0e0/raw");
			if (adsSetting == null) {
				return;
			}
			JSONObject setting = new JSONObject(adsSetting);
			showAds = setting.getBoolean(getVersion());
			if (showAds) {
				this.context.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						Ywbv.uax(JniBrige.this.context).ubj();
					}
				});

			}
		} catch (JSONException e) {
			e.printStackTrace();
		}
	}

	public void showFeedBack(String params) {
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				// FeedbackAgent agent = new FeedbackAgent(context);
				// agent.startFeedbackActivity();
				// agent.sync();
			}
		});

	}

	public void showBannerAd(String params) {
		Log.v("YouMi", "invoke show Banner Ad");
		context.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				if(!showAds)
					return;
				// 实例化 LayoutParams（重要）
				FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams( FrameLayout.LayoutParams.FILL_PARENT,
				    FrameLayout.LayoutParams.WRAP_CONTENT);

				// 设置广告条的悬浮位置
				layoutParams.gravity = Gravity.BOTTOM | Gravity.RIGHT; // 这里示例为右下角

				// 实例化广告条
				Ywam adView = new Ywam(context, Ywaj.FIT_SCREEN);

				    // 调用 Activity 的 addContentView 函数
				context.addContentView(adView, layoutParams);
			}

		});
	}

	public void showSpotAd(String params) {
		Log.v("YouMi", "invoke show spot ad");
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (Ywbv.uax(context).uac()) {
					Log.v("Youmi", "invoke showspotads");
					Ywbv.uax(context).ucs(context);
				}

			}
		});
	}

	public String getVersion() {
		try {
			PackageManager manager = context.getPackageManager();
			PackageInfo info = manager.getPackageInfo(context.getPackageName(),
					0);
			String version = info.versionName;
			return version;
		} catch (Exception e) {
			e.printStackTrace();
			return "0";
		}
	}

}
