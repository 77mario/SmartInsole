import { Component } from '@angular/core';

import { HomePage } from '../home/home';
import { AnalyticsPage } from '../analytics/analytics';
import { ConnectionPage } from '../connection/connection';


@Component({
  templateUrl: 'tabs.html'
})
export class TabsPage {

  tab1Root = HomePage;
  tab2Root = AnalyticsPage;
  tab3Root = ConnectionPage;
  constructor() {

  }
}
