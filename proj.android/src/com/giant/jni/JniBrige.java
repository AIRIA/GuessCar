package com.giant.jni;



import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.util.Log;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

import com.baidu.mobads.AdView;
import com.baidu.mobads.AdViewListener;
import com.baidu.mobads.IconsAd;
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
						/* 轮盘广告 */
						IconsAd iconsAd = new IconsAd(JniBrige.this.context);
						iconsAd.loadAd(JniBrige.this.context);
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
				RelativeLayout layout = new RelativeLayout(context);
				// 创建广告View
				AdView adView = new AdView(context);
				// 设置监听器
				adView.setListener(new AdViewListener() {
					public void onAdSwitch() {
						Log.w("", "onAdSwitch");
					}

					public void onAdShow(JSONObject info) {
						Log.w("", "onAdShow " + info.toString());
					}

					public void onAdReady(AdView adView) {
						Log.w("", "onAdReady " + adView);
					}

					public void onAdFailed(String reason) {
						Log.w("", "onAdFailed " + reason);
					}

					public void onAdClick(JSONObject info) {
						Log.w("", "onAdClick " + info.toString());
					}

					public void onVideoStart() {
						Log.w("", "onVideoStart");
					}

					public void onVideoFinish() {
						Log.w("", "onVideoFinish");
					}

					@Override
					public void onVideoClickAd() {
						Log.w("", "onVideoFinish");
					}

					@Override
					public void onVideoClickClose() {
						Log.w("", "onVideoFinish");
					}

					@Override
					public void onVideoClickReplay() {
						Log.w("", "onVideoFinish");
					}

					@Override
					public void onVideoError() {
						Log.w("", "onVideoFinish");
					}
				});
				
				context.addContentView(layout, new LayoutParams(LayoutParams.MATCH_PARENT,
						LayoutParams.MATCH_PARENT));
				RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(
						LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT);
				layoutParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
				layout.addView(adView, layoutParams);
			}

		});
	}

	public void showSpotAd(String params) {
		Log.v("YouMi", "invoke show spot ad");
		context.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				

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
